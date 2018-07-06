/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 05:40:47 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 05:40:53 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"
#include "ft_memory.h"

/*
** Handle controls. If Esc (27) or q is pressed, return True, which means to end
** vizualization
*/

t_bool	handle_controls(t_map *map, int ch)
{
	if (ch == 27 || ch == 'q')
		return (True);
	else if (ch == ' ')
		map->viz->active = (t_bool)!map->viz->active;
	else if (ch == 'e')
		map->viz->max_cyc_sec += map->viz->max_cyc_sec < 2491 ? 10 : 0;
	else if (ch == 'w')
		map->viz->max_cyc_sec += map->viz->max_cyc_sec < 2500 ? 1 : 0;
	else if (ch == 'd')
		map->viz->max_cyc_sec -= map->viz->max_cyc_sec >= 10 ? 10 : 0;
	else if (ch == 's')
		map->viz->max_cyc_sec -= map->viz->max_cyc_sec >= 1 ? 1 : 0;
	else if(ch == 'p')
		map->viz->sound = (t_bool)!map->viz->sound;
	return (False);
}

/*
** Routine used by second thread to unconditionally update vizualization every
** 500ms or so
*/

void	*viz_routine(void *arg)
{
	while (42)
	{
		viz_arena(arg);
		usleep(50000);
	}
	pthread_exit(NULL);
}

/*
** Add special character
*/

void	add_special(t_map *map, t_uint pos, chtype c, int n_cycles)
{
	t_special	*sp;

	sp = ft_memalloc(sizeof(t_special));
	sp->i = pos;
	sp->col = c;
	sp->n_cycles = n_cycles;
	sp->next = map->viz->spec;
	map->viz->spec = sp;
}
