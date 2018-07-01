/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 04:46:12 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 04:46:21 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Pronounce game to be over.
*/

void	game_over(t_map *map)
{
	to_log(map, "Contestant %d, \"%s\", has won !\n", map->last_alive_i + 1,
			map->bots[map->last_alive_i]->header->name);
	if (map->viz_mode)
	{
		map->viz->active = False;
		to_log(map, "Game is over. Press any key to finish");
		viz_arena(map);
		wgetch(map->viz->wmain);
	}
}

/*
** Game loop
*/

void	game_loop(t_map *map)
{
	while (map->pref->cycles_to_die >= 0 && !map->game_over)
	{
		dump_if_necessary(map);
		update_procs(map);
		handle_period(map);
	}
	game_over(map);
}

/*
** Game loop for visualization
*/

void	vgame_loop(t_map *map)
{
	pthread_t	vizthr;
	struct timeval	start;
	int				ch;
	int				cycles;

	pthread_create(&vizthr, NULL, viz_routine, map);
	gettimeofday(&start, NULL);
	cycles = map->cyc_cnt;
	while ((ch = getch()))
	{
		if (map->log->level & v_mouse && ch != ERR)
			to_log(map, "Key pressed: %c | %d\n", ch, ch);
		if (handle_controls(map, ch))
			return ;
		if (!map->viz->active || !map->viz->max_cyc_sec)
			continue ;
		dump_if_necessary(map);
		update_procs(map);
		handle_period(map);
		if (map->game_over)
			return game_over(map);
		handle_time(map, &start, &cycles);
	}
	pthread_exit(NULL);
}
