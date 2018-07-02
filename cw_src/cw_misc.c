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
