/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 13:25:34 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 13:25:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Game loop
*/

void	game_loop(t_map *map)
{
	while (map->pref.cycles_to_die >= 0 && any_proc_alive(map->procs))
	{

		update_procs(map);
		if (map->viz.on)
			viz_arena(&map->viz, map);
		map->cyc_cur++;
		map->cyc_cnt++;
		if (map->cyc_cur == map->pref.cycles_to_die)
		{
			map->pref.cycles_to_die -= map->pref.cycle_delta;
			map->cyc_cur = 0;
		}
	}
}

/*
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;

	set_default_pref(&map);
	parse_cli(&map, ac, av);

	if (map.viz.on)
		init_viz(&map.viz);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_essential)
	{
//		show_bots(map.bots, map.n_bots);
		show_map(&map);
	}
//	show_procs(map.procs);

//	for (int i = 0; i < 100; ++i)
//	{
//
//	}
	if (map.viz.on)
		wrapup_viz(&map.viz);
	return (0);
}
