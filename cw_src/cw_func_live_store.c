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
	int	i;

	log_more(map, "Process %d pronounced alive\n", pr->index);
	pr->alive = True;
	pr->last_live = map->cyc_cnt;
	if ((i = p_index_from_id(map, pr->args[0].value)) == -1)
		return log_more(map, "No player with id %d\n", pr->args[0].value);
	log_more(map, "Player %d: I'm alive!\n", i + 1);
	if (map->viz_mode)
		add_special(map, pr->pc, color_inv(map, i), 50);
	map->bots[i]->last_live = map->cyc_cnt + 1;
	map->bots[i]->lives++;
	map->lives_cur++;
	map->last_alive_i = i;
	return log_live(map, (t_uint)i);
}

/*
** Write value from T_REG, either on a map (T_IND) or to registry (T_REG)
*/

void	i_store(t_map *map, t_proc *pr)
{
	t_uint	val;

	val = get_reg(pr, pr->args[0].value);
	if (pr->args[1].type == T_REG)
		return set_reg(pr, get_arg(map, pr, 1), val);
	val_to_map(map, pr, pr->pc + ((short)pr->args[1].value % IDX_MOD), val);
}

/*
** Store value from the first arg (T_REG) by index on the map, starting from
** PC + (value of the second arg + value of the third arg)
*/

void	i_sti(t_map *map, t_proc *pr)
{
	t_uint	val;
	t_uint	start_pos;
	t_uint	first_arg;
	t_uint	sec_arg;

	val = get_reg(pr, pr->args[0].value);
	first_arg = get_arg(map, pr, 1);
	sec_arg = get_arg(map, pr, 2);
	start_pos = pr->pc + first_arg + sec_arg;
	log_sti(map, first_arg, sec_arg);
	val_to_map(map, pr, start_pos, val);
}

/*
** Move process pc if carry is one
*/

void	i_zjmp(t_map *map, t_proc *pr)
{
	if (pr->carry)
	{
		pr->pc += ((short)pr->args[0].value) % IDX_MOD;
		pr->jumped = True;
	}
	log_more(map, "Proc %d has jumped! New position: %u\n", pr->index, pr->pc);
}

/*
** Output argument as an ascii symbol
*/

void	i_aff(t_map *map, t_proc *pr)
{
	to_log(map, "%C", pr->args[0].value);
}
