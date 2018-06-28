/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bot_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:01:20 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/17 19:01:22 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "op.h"

/*
** Read <n> bytes from <fd>
*/

t_line	*read_n_bytes(int fd, unsigned int n)
{
	t_line	*res;
	ssize_t	nread;

	res = init_line();
	res->str = ft_memalloc(n + 1);
	if ((nread = read(fd, res->str, n)) == - 1)
		ft_panic(1, "Error reading file\n");
	else if (nread < n)
		ft_panic(1, "File has ended unexpectedly\n");
	res->len = n;
	return (res);
}


unsigned char	*find_magic(unsigned char *file)
{
	unsigned char	*first_four;
	int				i;
	int				j;

	first_four = ft_memalloc(sizeof(char) * 4);
	i = 0;
	j = 0;
	while (i < 4)
		first_four[j++] = file[i++];
	return (first_four);
}

char			*find_name(unsigned char *file)
{
	char			*name;
	int				i;
	int				j;

	name = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	i = 4;
	j = 0;
	while (i < PROG_NAME_LENGTH + 1)
		name[j++] = file[i++];
	j = 0;
	return (name);
}

char			*check_name(char *name)
{
	unsigned int	nbr;
	char			*ret;
	int				i;
	int				j;

	nbr = 0;
	i = 0;
	j = 0;
	ret = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	while (name[i] != 0)
	{
		nbr = 0;
		nbr = (nbr << 8) + name[i++];
		ret[j++] = nbr;
	}
	return (ret);
}
