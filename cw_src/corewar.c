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
** Initialize colors for vizualization.
** COLOR_WHITE is grey
** Colors:
**   - 1:
*/

void	init_color_table(void)
{
	start_color(); // allocate color table

	init_pair(1, COLOR_BLACK, COLOR_WHITE); // background
	init_pair(2, COLOR_WHITE, COLOR_BLACK); // map
	init_pair(3, COLOR_GREEN, COLOR_BLACK); // 1st bot
	init_pair(4, COLOR_BLUE, COLOR_BLACK); // 2nd bot
	init_pair(5, COLOR_RED, COLOR_BLACK); // 3rd bot
	init_pair(6, COLOR_CYAN, COLOR_BLACK); // 4th bot
	init_pair(7, COLOR_RED, COLOR_RED); // pure red for debugging purposes
}

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

	viz->h_main = 66;
	viz->w_main = 250;
	viz->wmain = newwin(viz->h_main, viz->w_main, 0, 0);
	viz->wmap = newwin(64, 193, 1, 2);
	viz->winfo = newwin(64, 52, 1, 196);

	attron(COLOR_PAIR(1));
//	for (int i = 0; i < viz->h; ++i)
//	{
//		for (int k = 0; k < viz->w; ++k)
//		{
//			mvaddch(i, k, ' ');
//		}
//	}
	attroff(COLOR_PAIR(1));
	wbkgd(viz->wmain, COLOR_PAIR(1));
	wbkgd(viz->wmap, COLOR_PAIR(2));
	wbkgd(viz->winfo, COLOR_PAIR(7));
}

void	wrapup_viz(t_viz *viz)
{
	(void)viz;
	endwin();
}

void	vmap(t_map *map, t_viz *viz)
{
//	static int	colors[4] = {COLOR_PAIR(1), COLOR_PAIR(2), COLOR_PAIR(3), COLOR_PAIR(4)};
	t_uint		i;
	t_uint		j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mvwprintw(viz->wmap, i, j * 3, " %02x ", map->map[i * 64 + j]);
			j++;
		}
		i++;
	}
}

void	viz_map(t_viz *viz, t_map *map)
{
	vmap(map, viz);
	wrefresh(viz->wmain);
	wrefresh(viz->wmap);
	wrefresh(viz->winfo);
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
		show_map(&map);
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
