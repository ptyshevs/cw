/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 08:15:56 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 08:17:13 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <viz.h>
#include "cw.h"

/*
** Convert player index to it's index in bots array
** Returns:
**   bot's id in range [0, map->n_bots) if found, otherwise -1
*/

int		p_index_from_id(t_map *map, int id)
{
	t_uint	i;

	i = 0;
	while (i < map->n_bots)
	{
		if (map->bots[i]->id == id)
			return ((int)i);
		i++;
	}
	return (-1);
}

/*
** Access method for process registry: get value stored in <n>th registry cell
*/

t_uint	get_reg(t_proc *pr, t_uint n)
{
	if (n <= 0 || n > 16)
//	{
//		log_more(map, "Tried to access invalid register (r%d)\n", n);
		return (0);
//	}
	return (pr->reg[n - 1]);
}

/*
** Setter for process register
*/

void	set_reg(t_proc *pr, t_uint n, t_uint v)
{
	if (n == 0 || n > 16)
		return ;
	pr->reg[n - 1] = v;
//			log_more(map, "i_add tried to write to r%d\n", pr->args[2].value);
}

/*
** Access method for indirect argument: Collect value from 4 bytes, starting
** from PC + (<ind_v> % IND_MOD)
*/

t_uint	get_indval(t_map *map, t_proc *pr, t_uint ind_v)
{
	t_uint	val;
	int		pos;
	t_uint	i;

	val = 0;
	i = 0;
	while (i < 4)
	{
		pos = pr->pc + (((short)ind_v) % IDX_MOD) + i;
		val = (val << 8) + get_map(map, pos);
		i++;
	}
	return (val);
}

/*
** Get index of the map
*/

t_uint	get_ind(t_proc *pr, t_uint v, t_bool is_long)
{
	short	pos;

	pos = (short)(is_long ? (short)v : ((short)v) % IDX_MOD);
	return (pr->pc + pos);
}

/*
** Write value <v> to map, starting from <n>-th byte
*/

void	val_to_map(t_map *map, t_proc *pr, t_uint n, t_uint v)
{
	t_uint	i;
	t_uc	byte;

	i = 0;
	while (i < 4)
	{
		byte = (t_uc)(v >> (8 * (3 - i)) & 0xFF);
		set_map(map, n + i, byte, bot_color_id(map, pr->id));
		i++;
	}
}

/*
** Get <n>-th argument of the current instruction, zero-indexed
*/

t_uint	get_arg(t_map *map, t_proc *pr, t_uint n)
{
	if (pr->args[n].type == T_DIR)
		return (pr->args[n].value);
	else if (pr->args[n].type == T_REG)
		return (get_reg(pr, pr->args[n].value));
	else
		return get_indval(map, pr, pr->args[n].value);
}
