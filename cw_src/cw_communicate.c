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
#include "viz.h"

/*
** Display usage
**
** Invoked when either no arguments were provided, or there is -h|--help option
** specified.
*/

void		show_usage(void)
{
	ft_printf("Usage: ./corewar [-d|--dump nbr_cycles N] [-s|--stream N]"
			" [-h|--help] [-v|--verbose <level>] [-z|--viz] [-c|--colorful] "
			"[-i|--identical] [[-n number] champion1.cor] ...\n\n");
	ft_printf("  -d --dump\tDump memory after N cycles then exits\n");
	ft_printf("  -s --stream\tDump memory every N cycles, pause, repeat\n");
	ft_printf("  -i --identical\tMake memory dump identical (typos included\n");
	ft_printf("  -c --colorful\tColorize memory dump\n");
	ft_printf("  -z --viz\tVizualization mode\n");
	ft_printf("  -h --help\tDisplay usage\n");
	ft_printf("  -v --verbose\tSet logger wordiness level (Add to combine):\n");
	ft_printf("    0 - Show essential info (bots, winner)\n");
	ft_printf("    1 - Show lives\n    2 - Show cycles\n");
	ft_printf("    4 - Show operations\n    8 - Show deaths\n");
	ft_printf("    16 - Show PC movements\n    32 - Show key pressed\n");
	ft_printf("    64 - Show registry state\n");
	ft_printf("    128 - Show even more details\n");
	ft_printf("\nVizualization key bindings:\n");
	ft_printf("  Esc, q\tquit vizualization\n");
	ft_printf("  Space\t\tStart or stop execution\n");
	ft_printf("  e\t\tIncrease cycles/sec limit by 10\n");
	ft_printf("  w\t\tIncrease cycles/sec limit by 1\n");
	ft_printf("  d\t\tDecrease cycles/sec limit by 10\n");
	ft_printf("  s\t\tDecrease cycles/sec limit by 1\n");
	ft_printf("  p\t\tPlay sound effects\n");
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

void	show_map(t_map *map, t_bool colorize)
{
	t_uint		i;
	char		*c;

	i = 0;
	while (i < MEM_SIZE)
	{
		c = colorize ? bot_strcolor(map->cmap[i]) : NULL;
		if (i == 0)
			ft_printf("0x0000 : ");
		else if (i % 64 == 0)
			ft_printf("%#06x : ", i);
		if (c)
			ft_printf(c);
		ft_printf("%02x ", map->map[i]);
		if (c)
			ft_printf("{nc}");
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

char	*arg_to_str(t_uc type)
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
			ft_printf("%02X: %s [%d]\n", args[i].code, arg_to_str(args[i].type),
					args[i].size);
		else
			ft_printf("%02X: %s [%d]\t<-- This should be zero\n",
				args[i].code, arg_to_str(args[i].type), args[i].size);
		i++;
	}
}
