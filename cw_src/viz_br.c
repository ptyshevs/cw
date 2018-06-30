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

/*
** Breakdown bar of 48 symbols int parts proportionally to number of lives of
** each player
*/

void	update_breakdown(t_map *map)
{
	t_uint	i;
	t_bot	*bot;

	i = 0;
	while (i < map->n_bots)
	{
		bot = map->bots[i];
		if (map->lives_cur == 0)
			map->viz->br[i] = 48 / map->n_bots;
		else
			map->viz->br[i] = (int)((float)bot->lives /
					(float)map->lives_cur * 48);
		i++;
	}
}

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
		wattron(viz->wlive, (c = get_bot_color_by_index(i, True)));
		while (m++ < br[i])
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
	update_breakdown(map);
	if (map->cyc_cnt && map->cyc_cur == 0)
		ft_memcpy(viz->prev_br, viz->br, sizeof(int) * map->n_bots);
	mvwprintw(viz->wlive, 1, 1, "Live breakdown for current period:");
	vperiod(map, viz, 3, viz->br);
	mvwprintw(viz->wlive, 5, 1, "Live breakdown for last period:");
	vperiod(map, viz, 7, viz->prev_br);
}
