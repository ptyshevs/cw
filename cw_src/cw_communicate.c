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
	ft_printf("    64 - Show registry state\n    128 - Show arguments type\n");
	ft_printf("    256 - Show even more details\n");
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
