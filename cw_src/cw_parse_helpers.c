/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:37:19 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 17:37:40 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Collect first <n> bytes from <bytes> into a single number
*/

unsigned int	bytes_to_uint(const t_uc *bytes, unsigned int n)
{
	unsigned int	i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while (i < n)
		nbr = (nbr << 8) + bytes[i++];
	return (nbr);
}

/*
** Read exactly <n> bytes from <fd>.
**
** Raises:
**   - InvalidFileError: read cannot be executed on the file
**   - UnexpectedEOF: read has returned lower number of bytes that was expected
**       to read
*/

t_line	*read_n_bytes(const char *filename, int fd, unsigned int n)
{
	t_line	*res;
	ssize_t	nread;

	res = init_line();
	res->str = ft_memalloc(n + 1);
	if ((nread = read(fd, res->str, n)) == - 1)
		ft_panic(1, "Error: invalid file %s\n", filename);
	else if (nread < n)
		ft_panic(1, "Error: file %s has ended unexpectedly\n", filename);
	res->len = n;
	return (res);
}

/*
** Store bots id (need to color processes for vizualization)
*/

void	collect_ids(t_map *map)
{
	t_uint	i;

	map->bot_ids = ft_memalloc(sizeof(int) * map->n_bots);
	i = 0;
	while (i < map->n_bots)
	{
		map->bot_ids[i] = map->bots[i]->id;
		i++;
	}
}
