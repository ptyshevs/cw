/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_func_live_store.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 06:23:22 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 06:23:43 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Make process alive for the current period
** Make player with index in T_DIR argument alive for the current period
*/

void	i_live(t_map *map, t_proc *pr)
{
	t_uint	i;

	to_log(map, "Process %d pronounced alive\n", pr->index);
	pr->alive = True;
	i = 0;
	while (i < map->n_bots)
	{
		if (map->bot_ids[i] == (int)pr->cur_args[0].value)
		{
			to_log(map, "Player %d: I'm alive!\n", i + 1);
			map->bots[i]->last_live = map->cyc_cnt;
			map->bots[i]->lives++;
			map->lives_cur++;
			return to_log(map, "Player %d pronounced alive %d times\n", i + 1,
					map->bots[i]->lives);
		}
		i++;
	}
	return to_log(map, "No player with id %d\n", pr->cur_args[0].value);
}

void	i_store(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}
void	i_sti(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}

void	i_zjmp(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}

void	i_aff(t_map *map, t_proc *pr)
{
	(void)map;
	(void)pr;
}
