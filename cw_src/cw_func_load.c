/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_func_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 06:21:23 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 06:22:07 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Load value into process' registry
**
** If first arg is T_DIR, write it directly into T_REG.
** Else if first arg is T_IND, write map->map[T_IND % IDX_MOD] to T_REG
*/

void	i_load(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, False);
	pr->carry = (t_uint)(val == 0);
	set_reg(pr, pr->args[1].value, val);
}


/*
** load value by index
*/

void	i_ldi(t_map *map, t_proc *pr)
{
	t_uint	val;
	t_uint	first_arg;
	t_uint	sec_arg;

	first_arg = get_arg(map, pr, 0, False);
	sec_arg = get_arg(map, pr, 1, False);
	val = pr->pc + first_arg + sec_arg;
	log_ldi(map, val, first_arg, sec_arg);
	val = get_indval(map, pr, val, False);
	set_reg(pr, pr->args[2].value, val);
}

void	i_lload(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, True);
	set_reg(pr, pr->args[1].value, val);
}

/*
**
*/

void	i_lldi(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, True) + get_arg(map, pr, 1, True);
	val = get_indval(map, pr, val, False);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}
