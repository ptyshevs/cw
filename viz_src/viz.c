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
#include "viz.h"

/*
** Initialize vizualization windows and set background colors
*/

void	init_viz_windows(t_map *map, t_viz *viz)
{
	viz->wmain = newwin(viz->h_main, viz->w_main, 0, 0);
	viz->wmap = newwin(64, 193, 1, 2);
	viz->winfo = newwin(8 + map->n_bots * 4, 52, 1, 196);
	viz->wlive = newwin(9, 52, 10 + map->n_bots * 4, 196);
	viz->wlog = newwin(map->log->length, map->log->width,
						20 + map->n_bots * 4, 196);
	wbkgd(viz->wmain, get_color("bg"));
	wbkgd(viz->wmap, get_color("map"));
	wbkgd(viz->winfo, get_color("map"));
	wbkgd(viz->wlive, get_color("map"));
	wbkgd(viz->wlog, get_color("map"));
}

/*
** Initialize everything that is needed for vizualization
** Notes:
**   - initscr() initializes terminal
**   - curs_set(0) makes cursor invisible
**   - noecho() disables echoing of input during getch()
**   - cbreak() disables line buffering
**   - keypad(strscr, true) enables key bindings
*/

void	init_viz(t_map *map)
{
	t_viz	*viz;

	initscr();
	curs_set(0);
	noecho();
	cbreak();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	timeout(0);
	init_color_table();
	viz = map->viz;
	viz->active = False;
	viz->h_main = 66;
	viz->w_main = 250;
	map->log->length = 29 + (4 - map->n_bots) * 4;
	map->log->width = 52;
	map->log->log = ft_memalloc(sizeof(char *) * map->log->length);
	viz->br = ft_memalloc(sizeof(int) * map->n_bots);
	viz->prev_br = ft_memalloc(sizeof(int) * map->n_bots);
	init_viz_windows(map, viz);
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

void	viz_arena(t_map *map)
{
	werase(map->viz->wlog);
	werase(map->viz->winfo);
	vmap(map, map->viz);
	vproc(map, map->viz);
	vinfo(map, map->viz);
	vbots(map, map->viz);
	vlive(map, map->viz);
	vlog(map, map->viz);
	wnoutrefresh(map->viz->wmain);
	wnoutrefresh(map->viz->wmap);
	wnoutrefresh(map->viz->winfo);
	wnoutrefresh(map->viz->wlive);
	wnoutrefresh(map->viz->wlog);
	doupdate();
}
