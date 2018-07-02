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
#include "viz.h"

/*
** Make process alive for the current period
** Make player with index in T_DIR argument alive for the current period
*/

void	i_live(t_map *map, t_proc *pr)
{
	t_uint	i;

	log_more(map, "Process %d pronounced alive\n", pr->index);
	pr->alive = True;
	pr->last_live = map->cyc_cnt;
	i = 0;
	while (i < map->n_bots)
	{
		if (map->bot_ids[i] == (int)pr->args[0].value)
		{
			log_more(map, "Player %d: I'm alive!\n", i + 1);
			if (map->viz_mode)
				add_special(map, pr->pc, color_inv(map->viz, i), 50);
			map->bots[i]->last_live = map->cyc_cnt + 1;
			map->bots[i]->lives++;
			map->lives_cur++;
			map->last_alive_i = i;
			return log_live(map, i);
		}
		i++;
	}
	return log_more(map, "No player with id %d\n", pr->args[0].value);
}

/*
** Write value from T_REG, either on a map (T_IND) or to registry (T_REG)
*/

void	i_store(t_map *map, t_proc *pr)
{
	if (pr->args[1].type == T_REG)
	{
		pr->reg[pr->args[1].value] = pr->reg[pr->args[0].value];
		return ;
	}
	set_map(map, pr->pc + (pr->args[1].value % IDX_MOD), (t_uc)pr->args[0].value);
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
