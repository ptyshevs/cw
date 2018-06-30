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
	ft_printf("Usage: ./corewar [-d|--dump nbr_cycles N] [-s|--stream N]"
			" [-h|--help] [-v|--verbose <1|2|3>] [-z] "
			"[[-n number] champion1.cor] ...\n\n");
	ft_printf("  -d --dump\tDump memory after N cycles then exits\n");
	ft_printf("  -s --stream\tDump memory every N cycles\n");
	ft_printf("  -h --help\tDisplay usage\n");
	ft_printf("  -v --verbose\tSet level of logger wordiness\n");
	ft_printf("    0 - Show essential info (bots, winner)\n");
	ft_printf("    1 - Show lives\n");
	ft_printf("    2 - Show cycles\n");
	ft_printf("    4 - Show operations\n");
	ft_printf("    8 - Show deaths\n");
	ft_printf("    16 - Show PC movements\n");
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
		if (i == 0)
			ft_printf("0x0000 : ");
		else if (i % 64 == 0)
			ft_printf("%#06x : ", i);
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
** Argument type string representation
*/

char	*arg_type_to_str(t_uc type)
{
	if (type == T_REG)
		return ("T_REG");
	else if (type == T_DIR)
		return ("T_DIR");
	else if (type == T_IND)
		return ("T_IND");
	else if (type == 0)
		return ("T_NAN");
	else
		return ("Unrecognized");
}

/*
** Display arguments decoded from codage
*/

void	show_args(t_arg *args)
{
	int	i;

	ft_printf("Arguments format: <code>: <type> [<size>]\n");
	i = 0;
	while (i < 4)
	{
		if (i < 3)
			ft_printf("%02X: %s [%d]\n", args[i].code, arg_type_to_str(args[i].type),
					args[i].size);
		else
			ft_printf("%02X: %s [%d]\t<-- This should be zero\n",
				args[i].code, arg_type_to_str(args[i].type), args[i].size);
		i++;
	}
}
