/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 04:43:50 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 04:43:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

/*
** Convert timeeval to seconds elapsed, in microseconds resolution
*/

double	te_to_sec(struct timeval te)
{
	return ((double)te.tv_sec * 1000000LL + (double)te.tv_usec);
}

double	time_diff(struct timeval x, struct timeval y)
{
	double x_ms, y_ms;

	x_ms = te_to_sec(x);
	y_ms = te_to_sec(y);
	return (y_ms - x_ms) / 1000000LL;
}

void	handle_time(t_map *map, struct timeval *start, int *cycles)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
		double td = time_diff(*start, end);
		double cyc_sec = (map->cyc_cnt - *cycles) / td;
		if (cyc_sec > map->viz->max_cyc_sec)
		{
			if (map->viz->max_cyc_sec >= 40)
				usleep((useconds_t) (20000 - map->viz->max_cyc_sec));
			else
				usleep((useconds_t) (10000 * (41 - map->viz->max_cyc_sec)));
		}
		if (td >= 1)
		{
			map->viz->cyc_sec = (map->cyc_cnt - *cycles) / td;
			gettimeofday(start, NULL);
			*cycles = map->cyc_cnt;
		}
}
