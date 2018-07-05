/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_func_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 06:25:01 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 06:25:14 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	i_fork(t_map *map, t_proc *pr)
{
	t_proc *new_proc;

	new_proc = create_proc(pr->id, pr->pc);
	new_proc->pc = get_ind(pr, get_arg(map, pr, 0), False) % MEM_SIZE;
	add_proc(&map->procs, new_proc);
}

/*
** Like fork, but creates process without % IDX_MOD
*/

void	i_lfork(t_map *map, t_proc *pr)
{
	t_proc	*new_pr;

	new_pr = create_proc(pr->id, pr->pc);
	new_pr->pc = get_ind(pr, get_arg(map, pr, 0), True) % MEM_SIZE;
	add_proc(&map->procs, new_pr);
}
