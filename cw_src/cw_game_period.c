/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_period.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 01:40:05 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/02 01:40:21 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Remove this process, update tracking variables and log if required
*/

void	rm_proc(t_map *map, t_proc **aproc)
{
	if (map->log->level & v_deaths)
		to_log(map, "Process %u hasn't lived for %d cycles (CTD %d)\n",
			(*aproc)->index, map->cyc_cnt - (*aproc)->last_live - 1,
			map->pref->cycles_to_die);
	ft_memdel((void **)aproc);
	map->n_proc--;
}

/*
** Remove processes that weren't declared alive. More specifically, delete all
** processes that haven't executed live instruction in the last period
** Set all processes to be "dead" - next period is starting.
*/

void	rm_dead_procs(t_map *map)
{
	t_proc	*iter;
	t_proc	*tmp;

	iter = map->procs;
	while (iter && !iter->alive)
	{
		tmp = iter;
		iter = iter->next;
		rm_proc(map, &tmp);
	}
	map->procs = iter;
	while (iter)
	{
		if (iter->alive)
			iter->alive = False;
		while (iter->next && !iter->next->alive)
		{
			tmp = iter->next;
			iter->next = tmp->next;
			rm_proc(map, &tmp);
		}
		iter = iter->next;
	}
}

/*
** Reset bot lives back to zero
*/

void	reset_bot_lives(t_map *map)
{
	t_uint	i;

	i = 0;
	while (i < map->n_bots)
		map->bots[i++]->lives = 0;
}

/*
** Breakdown bar of 48 symbols int parts proportionally to number of lives of
** each player
*/

void	update_breakdown(t_map *map)
{
	t_uint	i;
	t_bot	*bot;

	i = 0;
	while (i < map->n_bots)
	{
		bot = map->bots[i];
		if (map->lives_cur == 0)
			map->viz->br[i] = 48 / map->n_bots;
		else
			map->viz->br[i] = (int)((float)bot->lives /
					(float)map->lives_cur * 48);
		i++;
	}
}

/*
** Handle change of period
*/

void	handle_period(t_map *map)
{
	map->cyc_cur++;
	map->cyc_cnt++;
	if (map->log->level & v_cycles)
		to_log(map, "It is now cycle %d\n", map->cyc_cnt);
	if (map->viz_mode)
		update_breakdown(map);
	if (map->cyc_cur != map->pref->cycles_to_die)
		return ;
	if (map->lives_cur < NBR_LIVE && map->n_checks > 1)
		map->n_checks--;
	else if (map->lives_cur < NBR_LIVE && map->n_checks == 1)
	{
		map->pref->cycles_to_die -= map->pref->cycle_delta;
		map->n_checks = MAX_CHECKS;
	}
	else
		map->pref->cycles_to_die -= map->pref->cycle_delta;
	if (map->viz_mode)
		ft_memcpy(map->viz->prev_br, map->viz->br, sizeof(int) * map->n_bots);
	map->cyc_cur = 0;
	map->lives_cur = 0;
	reset_bot_lives(map);
	rm_dead_procs(map);
	if (map->pref->cycles_to_die <= 0 || !map->procs)
		map->game_over = True;
}
