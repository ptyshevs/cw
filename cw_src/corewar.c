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
** Initialize everything that is needed for vizualization
*/

void	init_viz(t_viz *viz)
{
	initscr(); // init terminal
	curs_set(0); // make cursor invisible
	noecho(); // disable echoing of input during getch()
	cbreak(); // disable line buffering
	keypad(stdscr, true);
	init_color_table();

	viz->active = True;
	viz->h_main = 66;
	viz->w_main = 250;
	viz->wmain = newwin(viz->h_main, viz->w_main, 0, 0);
	viz->wmap = newwin(64, 193, 1, 2);
	viz->winfo = newwin(24, 52, 1, 196);
	viz->wlog = newwin(40, 52, 25, 196);

	wbkgd(viz->wmain, get_color("bg"));
	wbkgd(viz->wmap, get_color("map"));
	wbkgd(viz->winfo, get_color("map"));
	wbkgd(viz->wlog, get_color("debug"));
}

void	wrapup_viz(t_viz *viz)
{
	(void)viz;
	endwin();
}


void	viz_map(t_viz *viz, t_map *map)
{
	vmap(map, viz);
	vproc(map, viz);
	vinfo(map, viz);
	vbots(map, viz);

	wrefresh(viz->wmain);
	wrefresh(viz->wmap);
	wrefresh(viz->winfo);
	wrefresh(viz->wlog);
	wgetch(viz->wmain); // replace with key bindings
//	getch();
}

/*
** Check if any of the processes is alive.
** One of the stopping conditions of game loop
*/

t_bool	any_proc_alive(t_proc *pr)
{
	while (pr)
	{
		if (pr->alive)
			return (True);
		pr = pr->next;
	}
	return (False);
}

/*
** Store bots id (need to color processes for vizualization)
*/

static void	collect_ids(t_map *map)
{
	t_uint	i;

	map->bot_ids = ft_memalloc(sizeof(int) * map->n_bots);
	i = 0;
	while (i < map->n_bots)
	{
		map->bot_ids[i] = map->bots[i]->id;
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
	collect_ids(&map);

	if (map.viz.on)
		init_viz(&map.viz);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_none)
	{
//		show_bots(map.bots, map.n_bots);
		show_map(&map);
	}
//	show_procs(map.procs);
	while (map.pref.cycles_to_die >= 0 && any_proc_alive(map.procs))
	{

		update_procs(&map);
		if (map.viz.on)
			viz_map(&map.viz, &map);
		map.cyc_cur++;
		map.cyc_cnt++;
		if (map.cyc_cur == map.pref.cycles_to_die)
		{
			map.pref.cycles_to_die -= map.pref.cycle_delta;
			map.cyc_cur = 0;
		}
	}
//	for (int i = 0; i < 100; ++i)
//	{
//
//	}
	if (map.viz.on)
		wrapup_viz(&map.viz);
	return (0);
}
