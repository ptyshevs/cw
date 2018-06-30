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
** Dump map state if necessary
*/

void	dump_if_necessary(t_map *map)
{
	char	*tmp;

	if (map->viz_mode || !map->dump.dump)
		return ;
	if (map->cyc_cur > 0 && map->cyc_cur % map->dump.n == 0)
	{
		if (map->dump.once)
		{
			show_map(map);
			exit(0);
		}
		show_map(map);
		ft_gnl(0, &tmp);
	}
}

/*
** Game loop
*/

void	game_loop(t_map *map)
{
	while (map->pref.cycles_to_die >= 0 && any_proc_alive(map->procs))
	{
		if (map->viz_mode)
			viz_arena(&map->viz, map);
		dump_if_necessary(map);
		update_procs(map);
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
** Add players introduction to log
*/

void	introduce_bots(t_map *map)
{
	t_uint		i;
	t_bot		*bot;

	i = 0;
	while (i < map->n_bots)
	{
		if (i == 0)
			to_log(map, "Introducing contestants...\n");
		bot = map->bots[i];
		to_log(map, "* Player %d, weighting %d bytes, \"%s\" (\"%s\")!\n",
			i + 1, bot->header->size, bot->header->name,
			bot->header->comment);
		i++;
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
		init_viz(&map.viz, &map.log, map.n_bots);
	introduce_bots(&map);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_essential)
	{
//		show_bots(map.bots, map.n_bots);
//		show_map(&map);
	}
//	show_procs(map.procs);
	game_loop(&map);
	if (map.viz_mode)
		wrapup_viz(&map.viz);
	return (0);
}
