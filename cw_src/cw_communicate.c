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
	t_uint		i;
	t_uint		m;

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

/*
** Display state of each process in the list
*/

void	show_procs(t_proc *procs)
{
	unsigned int	i;

	ft_printf("Processes output format <index>: <pc> [<id>] is <alive|dead>\n");
	i = 0;
	while (procs)
	{
		ft_printf(procs->alive ? "%u: %d [%d] is alive\n" :
				"%u: %d [%d] is dead\n", i++, procs->pc, procs->id);
		procs = procs->next;
	}
}

/*
** Display arguments decoded from codage
*/

void	show_args(t_uc *args)
{
	int	i;

	ft_printf("Arguments: ");
	i = 0;
	while (i < 3)
	{
		if (args[i] == T_REG)
			ft_printf(i + 1 < 3 && args[i + 1] > 0 ? "T_REG, " : "T_REG");
		else if (args[i] == T_DIR)
			ft_printf(i + 1 < 3 && args[i + 1] > 0 ? "T_DIR, " : "T_DIR");
		else if (args[i] == T_IND)
			ft_printf(i + 1 < 3 && args[i + 1] > 0 ? "T_IND, " : "T_IND");
		else if (args[i] == 0)
			;
		else
			ft_panic(1, "Unrecognized argument of size %d\n", args[i]);
		i++;
	}
	ft_printf("\n");
}
