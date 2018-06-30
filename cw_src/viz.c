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

void	init_viz(t_viz *viz, t_log *log, t_uint n_bots)
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
	log->length = 29 + (4 - n_bots) * 4;
	log->width = 52;
	viz->wmain = newwin(viz->h_main, viz->w_main, 0, 0);
	viz->wmap = newwin(64, 193, 1, 2);
	viz->winfo = newwin(8 + n_bots * 4, 52, 1, 196);
	viz->wlive = newwin(9, 52, 10 + n_bots * 4, 196);
	viz->wlog = newwin(log->length, log->width, 20 + n_bots * 4, 196);

	wbkgd(viz->wmain, get_color("bg"));
	wbkgd(viz->wmap, get_color("map"));
	wbkgd(viz->winfo, get_color("map"));
	wbkgd(viz->wlive, get_color("debug"));
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
** Main vizualization routine
*/

void	viz_arena(t_viz *viz, t_map *map)
{
	werase(viz->wlog);
	vmap(map, viz);
	vproc(map, viz);
	vinfo(map, viz);
	vbots(map, viz);
	vlog(map, viz);

	wrefresh(viz->wmain);
	wrefresh(viz->wmap);
	wrefresh(viz->winfo);
	wrefresh(viz->wlive);
	wrefresh(viz->wlog);
	wgetch(viz->wmain); // replace with key bindings
//	getch();
}
