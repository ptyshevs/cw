/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_viz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 21:51:33 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/29 21:51:50 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"


/*
** Vizualize process
*/

void	vproc(t_map *map, t_viz *viz)
{
	t_proc	*pr;

	pr = map->procs;
	while (pr)
	{
		if (!pr->alive)
			break ;
		int c = get_proc_color(map, pr->id);
		wattron(viz->wmap, c);
		mvwprintw(viz->wmap, pr->pc / 64, pr->pc % 64 * 3 + 1, "%02x", map->map[pr->pc]);
		wattroff(viz->wmap, c);
		pr = pr->next;
	}
}

void	vmap(t_map *map, t_viz *viz)
{
	static int	colors[4] = {COLOR_PAIR(3), COLOR_PAIR(5),
							COLOR_PAIR(7), COLOR_PAIR(9)};
	t_uint		i;
	t_uint		j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			t_uint m = 0;
			while (m < map->n_bots)
			{
			if (i * 64 + j == map->bots[m]->start_pos)
				wattron(viz->wmap, colors[m]);
			else if (i * 64 + j == map->bots[m]->start_pos + map->bots[m]->header->size)
				wattroff(viz->wmap, colors[m]);
			m++;
		}
			mvwprintw(viz->wmap, i, j * 3, " %02x ", map->map[i * 64 + j]);
			j++;
		}
		i++;
	}
}
