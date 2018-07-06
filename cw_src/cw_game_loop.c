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
		system("pkill afplay 2> /dev/null");
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
		if (map->log->level & v_cycles)
			to_log(map, "It is now cycle %d\n", map->cyc_cnt + 1);
		update_procs(map);
		handle_period(map);
	}
	game_over(map);
	if (map->dump->n > map->cyc_cnt)
		dump_if_necessary(map);
}

/*
** Update special symbols
*/

void	update_special(t_map *map, t_viz *viz)
{
	t_special	*it;
	t_special	*tmp;

	(void)map;
	it = viz->spec;
	while (it && it->n_cycles < 0)
	{
		tmp = it;
		it = it->next;
		ft_memdel((void **)&tmp);
	}
	viz->spec = it;
	while (it)
	{
		while (it->next && it->next->n_cycles < 0)
		{
			tmp = it->next->next;
			ft_memdel((void **)&it->next);
			it->next = tmp;
		}
		it->n_cycles--;
		it = it->next;
	}
}

/*
** Handle sound effects
*/

void	handle_sound(t_map *map, t_viz *viz)
{
	static t_song	songs[8] = {{"War sounds", "war.mp4"},
		{"Battlefield 1", "battlefield.mp4"},
		{"XXXTentacion - Look At Me", "xxxtentacion.3gp"},
		{"It's a trap", "nice_pony.mp4"},
		{"Snoop Dog - The Last Episode", "snoop.3gp"},
		{"Childish Gambino - Sweatpants", "sweatpants.3gp"},
		{"Vitas - 7th element", "vitas.3gp"},
		{"Childish Gambino - 3005", "3005.3gp"}};
	t_song			song;
	char			*tmp;

	if (viz->sound && !viz->playing)
	{
		song = songs[rand() % 8];
		tmp = ft_sprintf("afplay resources/%s&", song.filename);
		to_log(map, "Song playing: %s", song.name);
		system(tmp);
		ft_strdel(&tmp);
		viz->playing = True;
	}
	else if (!viz->sound && viz->playing)
	{
		system("pkill afplay 2> /dev/null");
		viz->playing = False;
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

	pthread_create(&map->viz->vizthr, NULL, viz_routine, map);
	gettimeofday(&start, NULL);
	cycles = map->cyc_cnt;
	while ((ch = getch()))
	{
		handle_sound(map, map->viz);
		if (map->log->level & v_keys && ch != ERR)
			to_log(map, "Key pressed: %c | %d\n", ch, ch);
		if (handle_controls(map, ch))
			return ;
		if (!map->viz->active || !map->viz->max_cyc_sec)
			continue ;
		dump_if_necessary(map);
		update_procs(map);
		update_special(map, map->viz);
		handle_period(map);
		if (map->game_over)
			return (game_over(map));
		handle_time(map, &start, &cycles);
	}
	pthread_exit(NULL);
}
