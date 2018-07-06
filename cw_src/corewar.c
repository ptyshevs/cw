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
#include "viz.h"

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
	collect_ids(&map);
	introduce_bots(&map);
	inhabit_map(&map);
	init_procs(&map);
	map.viz_mode ? vgame_loop(&map) : game_loop(&map);
	if (map.viz_mode)
		wrapup_viz(map.viz);
	return (0);
}
