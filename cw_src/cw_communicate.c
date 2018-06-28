/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:07:54 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/17 19:07:59 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Display usage
**
** Invoked when either no arguments were provided, or there is -h|--help option
** specified.
*/

void		show_usage(void)
{
	ft_printf("Usage: ./corewar [-d|--dump nbr_cycles] [-h|--help] "
			"[-v|--verbose <1|2|3>] [-z] "
			"[[-n number] champion1.cor] ...\n\n");
	ft_printf("  -d --dump\tDump memory after N cycles then exits\n");
	ft_printf("  -h --help\tDisplay usage\n");
	ft_printf("  -v --verbose\tSet level of logger wordiness\n");
	ft_printf("  -z\t\tVizualization mode\n");
	exit(1);
}

/*
** Display main info about each bot
*/

void	show_bots(t_bot **bots, unsigned int num_bots)
{
	unsigned int	i;

	ft_printf("Format: Bot <index> [<id>|<size>]: <comment>\n");
	i = 0;
	while (i < num_bots)
	{
		ft_printf("Bot %s [%d|%X]: %s\n", bots[i]->header->name,
		bots[i]->id, bots[i]->header->size, bots[i]->header->comment);
		i++;
	}
}

/*
** Display map
*/

void	show_map(t_map *map)
{
	static char	*colors[4] = {"{green}", "{blue}", "{red}", "{cyan}"};
	int			i;
	int			m;

	i = 0;
	while (i < MEM_SIZE)
	{
		m = 0;
		while (m < map->n_bots)
		{
			if (i == map->bots[m]->start_pos)
				ft_printf(colors[m]);
			else if (i == map->bots[m]->start_pos + map->bots[m]->header->size)
				ft_printf("{nc}");
			m++;
		}
		ft_printf((i + 1) % 64 ? "%02x " : "%02x", map->map[i]);
		if (++i % 64 == 0)
			ft_printf("\n");
	}
}
