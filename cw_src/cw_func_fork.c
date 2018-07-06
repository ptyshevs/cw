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
	t_proc	*new_pr;
	int		i;

	new_pr = create_proc(pr->id, pr->pc);
	new_pr->pc = get_ind(pr, get_arg(map, pr, 0, False), False) % MEM_SIZE;
	i = 0;
	while (i < 16)
	{
		new_pr->reg[i] = pr->reg[i];
		i++;
	}
	map->n_proc++;
	log_fork(map, pr, new_pr->pc);
	add_proc(&map->procs, new_pr);
}

/*
** Like fork, but creates process without % IDX_MOD
*/

void	i_lfork(t_map *map, t_proc *pr)
{
	t_proc	*new_pr;
	int		i;

	new_pr = create_proc(pr->id, pr->pc);
	new_pr->pc = get_ind(pr, get_arg(map, pr, 0, True), True) % MEM_SIZE;
	i = 0;
	while (i < 16)
	{
		new_pr->reg[i] = pr->reg[i];
		i++;
	}
	map->n_proc++;
	log_fork(map, pr, new_pr->pc);
	add_proc(&map->procs, new_pr);
}
