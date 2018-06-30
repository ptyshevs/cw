/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:36:32 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/30 14:36:49 by ptyshevs         ###   ########.fr       */
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
	wbkgd(viz->wlog, get_color("map"));
}

/*
** End vizualization
*/

void	wrapup_viz(t_viz *viz)
{
	(void)viz;
	endwin();
}

/*
** Vizualize log - store list of K last messages, redrawing it on every iteration
*/

void	vlog(t_map *map, t_viz *viz)
{
	(void)map;
	mvwprintw(viz->wlog, 1, 1, "hi");
}

/*
** Main vizualization routine
*/

void	viz_arena(t_viz *viz, t_map *map)
{
	vmap(map, viz);
	vproc(map, viz);
	vinfo(map, viz);
	vbots(map, viz);
	vlog(map, viz);

	wrefresh(viz->wmain);
	wrefresh(viz->wmap);
	wrefresh(viz->winfo);
	wrefresh(viz->wlog);
	wgetch(viz->wmain); // replace with key bindings
//	getch();
}
