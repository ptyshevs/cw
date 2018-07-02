/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_br.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:10:43 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 00:10:53 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Vizualize period bar on the <height> specified
*/

void	vperiod(t_map *map, t_viz *viz, int height, const int *br)
{
	t_uint	k;
	int		m;
	t_uint	i;
	chtype	c;

	mvwaddch(viz->wlive, height, 1, '[');
	k = 2;
	i = 0;
	while (i < map->n_bots)
	{
		m = 0;
		wattron(viz->wlive, (c = bot_color(map, i)));
		while (m++ < br[i] && k < 50)
			mvwaddch(viz->wlive, height, k++, '-');
		wattroff(viz->wlive, c);
		i++;
	}
	while (k < 50)
		mvwaddch(viz->wlive, height, k++, '-');
	mvwaddch(viz->wlive, height, 50, ']');
}

/*
** Vizualize live breakdown
*/

void	vlive(t_map *map, t_viz *viz)
{
	mvwprintw(viz->wlive, 1, 1, "Live breakdown for current period:");
	vperiod(map, viz, 3, viz->br);
	mvwprintw(viz->wlive, 5, 1, "Live breakdown for last period:");
	vperiod(map, viz, 7, viz->prev_br);
}

/*
** Vizualize special characters
*/

void	vspec(t_map *map, t_viz *viz)
{
	t_special	*it;

	it = viz->spec;
	while (it)
	{
		if (it->n_cycles >= 0)
		{
			wattron(viz->wmap, it->col);
			mvwprintw(viz->wmap, it->i / 64, it->i % 64 * 3 + 1, "%02x",
					map->map[it->i]);
			wattroff(viz->wmap, it->col);
		}
		it = it->next;
	}
}
