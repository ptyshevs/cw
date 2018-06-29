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
	start_color(); // allocate color table

	init_pair(1, COLOR_BLACK, COLOR_RED);

	viz->h = 20;
	viz->w = 40;
	viz->wmain = newwin(viz->h, viz->w, 0, 0);
	attron(COLOR_PAIR(1));
	for (int i = 0; i < viz->h; ++i)
	{
		for (int k = 0; k < viz->w; ++k)
		{
			mvaddch(i, k, ' ');
		}
	}
	attroff(COLOR_PAIR(1));
	wbkgd(viz->wmain, COLOR_PAIR(1));
	box(viz->wmain, '$', '$');
}

void	wrapup_viz(t_viz *viz)
{
	(void)viz;
	endwin();
}

void	viz_map(t_viz *viz, t_map *map)
{
	(void)viz;
	(void)map;
	wprintw(viz->wmain, "Hello world");
	wrefresh(viz->wmain);
	wgetch(viz->wmain);
//	getch();
}

/*
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;

	map.log.level = v_none;
	map.log.to = 1;
	parse_cli(&map, ac, av);
	if (map.viz.on)
		init_viz(&map.viz);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_none)
	{
//		show_bots(map.bots, map.n_bots);
//		show_map(&map);
	}
//	show_procs(map.procs);
	if (map.viz.on)
		viz_map(&map.viz, &map);
//	for (int i = 0; i < 100; ++i)
//	{
//		exec(&map, map.procs);
//	}
	if (map.viz.on)
		wrapup_viz(&map.viz);
	return (0);
}
