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
	while (map->pref->cycles_to_die >= 0 && any_proc_alive(map->procs))
	{
		if (map->viz_mode)
			viz_arena(map->viz, map);
		dump_if_necessary(map);
		update_procs(map);
		map->cyc_cur++;
		map->cyc_cnt++;
		if (map->cyc_cur == map->pref->cycles_to_die)
		{
			map->pref->cycles_to_die -= map->pref->cycle_delta;
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
	if (map.viz_mode)
		init_viz(&map);
	introduce_bots(&map);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log->level > v_essential)
	{
//		show_bots(map.bots, map.n_bots);
//		show_map(&map);
	}
//	show_procs(map.procs);
	game_loop(&map);
	if (map.viz_mode)
		wrapup_viz(map.viz);
	return (0);
}
