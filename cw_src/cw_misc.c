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
