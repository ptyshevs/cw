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
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;

	map.log.level = v_none;
	map.log.to = 1;
	parse_cli(&map, ac, av);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_none)
	{
		show_bots(map.bots, map.n_bots);
		show_map(&map);
	}
	return (0);
}
