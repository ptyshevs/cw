/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_map_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 23:54:41 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/06 23:54:53 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Set default pref for map
*/

void	set_default_pref(t_map *map)
{
	map->log = ft_memalloc(sizeof(t_log));
	map->pref = ft_memalloc(sizeof(t_pref));
	map->dump = ft_memalloc(sizeof(t_dump));
	map->viz = ft_memalloc(sizeof(t_viz));
	ft_memset(map->cmap, UINT32_MAX, sizeof(chtype) * MEM_SIZE);
	map->viz->max_cyc_sec = 50;
	map->n_checks = MAX_CHECKS;
	map->log->to = 1;
	map->pref->cycles_to_die = CYCLE_TO_DIE;
	map->pref->cycle_delta = CYCLE_DELTA;
	map->pref->max_checks = MAX_CHECKS;
	map->pref->nbr_live = NBR_LIVE;
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
