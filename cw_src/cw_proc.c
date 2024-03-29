/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 21:52:12 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 21:52:23 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Create process, put id to the first cell of the regisry.
*/

t_proc	*create_proc(t_uint id, t_uint pos)
{
	static t_uint	index = 1;
	t_proc			*pr;

	pr = ft_memalloc(sizeof(t_proc));
	pr->alive = True;
	pr->pc = pos;
	pr->reg[0] = id;
	pr->id = id;
	pr->index = index++;
	return (pr);
}

/*
** Add process to the process list. This will satisfy the requirement
** such that the last bot begins first.
*/

void	add_proc(t_proc **ahead, t_proc *pr)
{
	pr->next = *ahead;
	*ahead = pr;
}

/*
** Place processes at the beginning of executable code of each bot.
*/

void	init_procs(t_map *map)
{
	t_proc	*pr;
	t_uint	m;

	m = 0;
	while (m < map->n_bots)
	{
		pr = create_proc((t_uint)map->bots[m]->id, map->bots[m]->start_pos);
		add_proc(&map->procs, pr);
		map->n_proc++;
		m++;
	}
}
