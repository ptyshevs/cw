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
# include <ncurses.h>
# include <sys/time.h>
# include <pthread.h>
# include "structs.h"

/*
** Vizualization
*/

void		init_color_table(t_viz *viz);
chtype		get_color(t_viz *viz, char *color);
chtype		get_ctable(t_viz *viz, int i);
short		color_index(t_viz *viz, chtype col);
chtype		bot_color(t_map *map, int index);
chtype		bot_color_id(t_map *map, int id);
chtype		color_inv(t_map *map, int index);
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
void		vspec(t_map *map, t_viz *viz);

void		add_special(t_map *map, t_uint pos, chtype c, int n_cycles);

void		handle_time(t_map *map, struct timeval *start, int *cycles);
t_bool		handle_controls(t_map *map, int ch);

#endif
