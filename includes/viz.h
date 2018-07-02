/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:39:05 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 00:39:29 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZ_H
# define VIZ_H
# include "cw.h"
# include <ncurses.h>
# include <sys/time.h>
# include <pthread.h>

/*
** Color structure
*/

typedef struct	s_col
{
	char	*name;
	chtype	c;
	int		n;
}				t_col;

/*
** Structure for vizualization
** Fields:
**    - h_main: height of the main window
**    - w_main: width of the main window
**    - wmain: main window
**    - wmap: map window
**    - winfo: information window
**    - wlive: live breakdown window
**    - wlog: logging window
**
**    - br: breakdown of lives for the current period
**    - prev_br: breakdown for the previous period
**    - active: whether viz is running or paused
**    - max_cyc_sec: max cycles per second
**    - cyc_sec: current cycles per second ratio
*/

typedef struct	s_viz
{
	int		h_main;
	int		w_main;

	WINDOW	*wmain;
	WINDOW	*wmap;
	WINDOW	*winfo;
	WINDOW	*wlive;
	WINDOW	*wlog;

	int		*br;
	int		*prev_br;
	t_col	*col_table[11];
	t_bool	active;
	t_bool	sound;
	int		max_cyc_sec;
	double	cyc_sec;
}				t_viz;

/*
** Vizualization
*/

void		init_color_table(t_viz *viz);
chtype		get_color(t_viz *viz, char *color);
chtype		get_ctable(t_viz *viz, int i);
short		color_index(t_viz *viz, chtype col);
int			get_proc_color(t_map *map, int id);
chtype		bot_color(t_viz *viz, int index);
char		*bot_strcolor(int index);

void		init_viz(t_map *map);
void		wrapup_viz(t_viz *viz);
void		viz_arena(t_map *map);
void		*viz_routine(void *arg);

void		vproc(t_map *map, t_viz *viz);
void		vmap(t_map *map, t_viz *viz);
void		vinfo(t_map *map, t_viz *viz);
void		vbots(t_map *map, t_viz *viz);
void		vlive(t_map *map, t_viz *viz);
void		vlog(t_map *map, t_viz *viz);

void		handle_time(t_map *map, struct timeval *start, int *cycles);
t_bool		handle_controls(t_map *map, int ch);;

#endif
