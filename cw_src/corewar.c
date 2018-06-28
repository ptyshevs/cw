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

	map.log_to = 2;
	parse_cli(&map, ac, av);
	logging((char *)42, (map.v ? (char *)(t_vrb)map.v : (char *)v_standard),
			(char *)1);
	show_bots(map.bots, map.num_players);
	inhabit_map(&map);
	show_map(&map);
	return (0);
}
