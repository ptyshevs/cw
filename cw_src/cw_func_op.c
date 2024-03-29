/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_func_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 06:18:53 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 06:19:06 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** T_REG (0) + T_REG (1) -> T_REG (2)
*/

void	i_add(t_map *map, t_proc *pr)
{
	t_uint	val;

	(void)map;
	val = get_reg(pr, pr->args[0].value) + get_reg(pr, pr->args[1].value);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}

/*
** T_REG(0) - T_REG(1) -> T_REG(2)
*/

void	i_sub(t_map *map, t_proc *pr)
{
	t_uint	val;

	(void)map;
	val = get_reg(pr, pr->args[0].value) - get_reg(pr, pr->args[1].value);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}

/*
** arg(0) and arg(1) can be of any type
** arg(0) & arg(1) -> T_REG(2)
*/

void	i_and(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, False) & get_arg(map, pr, 1, False);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}

/*
** arg(0) and arg(1) can be of any type
** arg(0) | arg(1) -> T_REG(2)
*/

void	i_or(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, False) | get_arg(map, pr, 1, False);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}

/*
** arg(0) and arg(1) can be of any type
** arg(0) ^ arg(1) -> T_REG(2)
*/

void	i_xor(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_arg(map, pr, 0, False) ^ get_arg(map, pr, 1, False);
	set_reg(pr, pr->args[2].value, val);
	pr->carry = (t_uint)(val == 0);
}
