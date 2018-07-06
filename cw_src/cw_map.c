/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:36:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 20:36:26 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Inhabit map with bots and initialize cmap
*/

void	inhabit_map(t_map *map)
{
	t_uint		to_place;
	t_uint		i;
	t_uint		k;
	t_uint		m;

	to_place = MEM_SIZE / map->n_bots;
	m = 0;
	while (m < map->n_bots)
	{
		i = 0;
		k = to_place * m;
		map->bots[m]->start_pos = k;
		while (i < map->bots[m]->header->size)
		{
			map->map[k] = map->bots[m]->code[i++];
			map->cmap[k++] = bot_color(map, m);
		}
		m++;
	}
}

/*
** Move process <pr> <n> cells forward on a map.
*/

void	move_proc(t_map *map, t_proc *pr, int n)
{
	if (map->log->level & v_pc && n > 1)
		log_move(map, pr, n);
	pr->pc = (pr->pc + n) % MEM_SIZE;
}

/*
** Get value from circular map
*/

t_uint	get_map(t_map *map, int n)
{
	return (map->map[(MEM_SIZE + (n % MEM_SIZE)) % MEM_SIZE]);
}

chtype	get_cmap(t_map *map, int n)
{
	return (map->cmap[(MEM_SIZE + (n % MEM_SIZE)) % MEM_SIZE]);
}

/*
** Set value to circular map
*/

void	set_map(t_map *map, int n, t_uc v, chtype who)
{
	map->map[(MEM_SIZE + (n % MEM_SIZE)) % MEM_SIZE] = v;
	map->cmap[(MEM_SIZE + (n % MEM_SIZE)) % MEM_SIZE] = who;
}
