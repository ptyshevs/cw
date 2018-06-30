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
	wbkgd(viz->wlive, get_color("map"));
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
** Breakdown bar of 48 symbols int parts proportionally to number of lives of
** each player
*/

int		*breakdown(t_map *map)
{
	int		*br;
	t_uint	i;
	t_bot	*bot;

	br = ft_memalloc(sizeof(int) * map->n_bots);
	i = 0;
	while (i < map->n_bots)
	{
		bot = map->bots[i];
		if (map->lives_cur == 0)
			br[i] = 48 / map->n_bots;
		else
			br[i] = (int)((float)bot->lives / (float)map->lives_cur * 48);
		i++;
	}
	return (br);
}

/*
** Vizualize period bar on the <height> specified
*/

void	vperiod(t_map *map, t_viz *viz, int height, int *br)
{
	t_uint	k;
	int		m;
	t_uint	i;
	chtype	c;

	if (!br)
	{
		mvwprintw(viz->wlive, height, 1, "[------------------------------------------------]");
		return ;
	}

	mvwaddch(viz->wlive, height, 1, '[');
	k = 2;
	i = 0;
	while (i < map->n_bots)
	{
		m = 0;
		wattron(viz->wlive, (c = get_bot_color_by_index(i, True)));
		while (m++ < br[i])
			mvwaddch(viz->wlive, height, k++, '-');
		wattroff(viz->wlive, c);
		i++;
	}
	mvwaddch(viz->wlive, height, 50, ']');
}

/*
** Vizualize live breakdown
*/

void	vlive(t_map *map, t_viz *viz)
{

	if (viz->br)
		ft_memdel((void **)&viz->br);
	viz->br = breakdown(map);
	if (map->cyc_cnt && map->cyc_cur == 0)
	{
		if (viz->prev_br)
			ft_memdel((void **)&viz->prev_br);
		viz->prev_br = viz->br;
	}
	mvwprintw(viz->wlive, 1, 1, "Live breakdown for current period:");
	vperiod(map, viz, 3, viz->br);
//	mvwprintw(viz->wlive, 3, 1, "[------------------------------------------------]");
	mvwprintw(viz->wlive, 5, 1, "Live breakdown for last period:");
	vperiod(map, viz, 5, viz->prev_br);
//	mvwprintw(viz->wlive, 7, 1, "[------------------------------------------------]");
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
	vlive(map, viz);
	vlog(map, viz);

	wrefresh(viz->wmain);
	wrefresh(viz->wmap);
	wrefresh(viz->winfo);
	wrefresh(viz->wlive);
	wrefresh(viz->wlog);
	wgetch(viz->wmain); // replace with key bindings
//	getch();
}
