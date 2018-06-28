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

t_bot			*init_bot(void)
{
	t_bot			*bot;

	bot = ft_memalloc(sizeof(t_bot));
	bot->header = ft_memalloc(sizeof(t_header));
	return (bot);
}

unsigned int	check_magic(unsigned char *magic)
{
	unsigned int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (i < 4)
		nbr = (nbr << 8) + magic[i++];
	if (nbr != COREWAR_EXEC_MAGIC)
		ft_panic("Magic is bad", 2, 1);
	return (nbr);
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
