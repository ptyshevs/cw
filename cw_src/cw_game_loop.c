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
** Pronounce game to be over.
** TODO: Show winner
*/

void	game_over(t_map *map)
{
	if (map->viz_mode)
	{
		to_log(map, "Game is over. Press any key to finish");
		viz_arena(map->viz, map);
		wgetch(map->viz->wmain);
	}
	else
		ft_dprintf(2, "GAME IS OVER\n");
}

t_bool	handle_controls(t_map *map, int ch)
{
	if (ch == 27)
			return (True);
	else if (ch == ' ')
		map->viz->active = (t_bool)!map->viz->active;
	else if (ch == 'e')
		map->viz->max_cyc_sec += map->viz->max_cyc_sec < 2500 ? 10 : 0;
	else if (ch == 'w')
		map->viz->max_cyc_sec += map->viz->max_cyc_sec < 2500 ? 1 : 0;
	else if (ch == 'd')
		map->viz->max_cyc_sec -= map->viz->max_cyc_sec >= 10 ? 10 : 0;
	else if (ch == 's')
		map->viz->max_cyc_sec -= map->viz->max_cyc_sec >= 1 ? 1 : 0;
	return (False);
}


void	handle_period(t_map *map)
{
	map->cyc_cur++;
	map->cyc_cnt++;
	if (map->cyc_cur == map->pref->cycles_to_die)
	{
		map->pref->cycles_to_die -= map->pref->cycle_delta;
		map->cyc_cur = 0;
	}
}

/*
** Game loop for visualization
*/

void	vgame_loop(t_map *map)
{
	struct timeval	start;
	int				ch;
	int				cycles;

	gettimeofday(&start, NULL);
	cycles = map->cyc_cnt;
	while ((ch = getch()))
	{
		if (handle_controls(map, ch))
			return ;
		viz_arena(map->viz, map);
		if (!map->viz->active || !map->viz->max_cyc_sec)
			continue ;
		if (map->pref->cycles_to_die <= 0 || !any_proc_alive(map->procs))
			return game_over(map);
		dump_if_necessary(map);
		update_procs(map);
		handle_period(map);
		handle_time(map, &start, &cycles);
	}
}
