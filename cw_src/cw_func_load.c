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
	t_uint	r;
	t_uint	val;

	r = get_reg(pr, pr->args[1].value);
	if (pr->args[0].type == T_DIR)
	{
		pr->reg[r] = pr->args[0].value;
		return ;
	}
	t_uint	i_from = pr->pc + ((short)pr->args[0].value) % IDX_MOD;
	val = collect_arg(map, pr->cur_ins->label_size, i_from, 0);
	pr->reg[r] = val;
	pr->carry = (t_uint)(val == 1);
}

t_uint	get_arg(t_map *map, t_proc *pr, t_arg arg)
{
	if (arg.type == T_REG)
		return (get_reg(pr, arg.value));
	else if (arg.type == T_DIR)
		return (arg.value);
	return collect_arg(map, 4, pr->pc + ((short)pr->args[0].value) % IDX_MOD, 0);
}

/*
** load value by index
*/

void	i_ldi(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, pr->args[0]) + get_arg(map, pr, pr->args[1]);
	val = collect_arg(map, 4, (pr->pc + val) % IDX_MOD, 0);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 1);
}

void	i_lload(t_map *map, t_proc *pr)
{
	t_uint	r;
	t_uint	val;

	r = get_reg(pr, pr->args[1].value);
	if (pr->args[0].type == T_DIR)
	{
		pr->reg[r] = pr->args[0].value;
		return ;
	}
	val = collect_arg(map, pr->cur_ins->label_size, pr->pc + ((short)pr->args[0].value), 0);
	set_reg(pr, pr->args[1].value, val);
	pr->carry = (t_uint)(val == 1);
}

/*
**
*/

void	i_lldi(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, pr->args[0]) + get_arg(map, pr, pr->args[1]);
	val = collect_arg(map, 4, pr->pc + val, 0);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 1);
}
