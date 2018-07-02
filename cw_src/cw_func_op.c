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

	val = pr->args[0].value + pr->args[1].value;
	if (pr->args[2].value < 16)
		pr->reg[pr->args[2].value] = val;
	else
		log_more(map, "i_add tried to write to r%d\n", pr->args[2].value);
}

void	i_sub(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}

void	i_and(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}

void	i_or(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}

void	i_xor(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}
