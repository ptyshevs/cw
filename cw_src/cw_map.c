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

/*
** Inhabit map with bots
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
			map->map[k++] = map->bots[m]->code[i++];
		m++;
	}
}


/*
** Move process <pr> <n> cells forward on a map.
*/

void	move_proc(t_map *map, t_proc *pr, t_uint n)
{
	log_move(map, pr, n);
	pr->pc = (pr->pc + n) % MEM_SIZE;
}

/*
** Get value from circular map
*/

t_uint	get_map(t_map *map, t_uint n)
{
	return (map->map[n % MEM_SIZE]);
}

/*
** Set value to circular map
*/

void	set_map(t_map *map, t_uint n, t_uc v)
{
	map->map[n % MEM_SIZE] = v;
}
