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
** Write <n> bytes to map, starting from <pc>, essentially breaking up <val>
** into bytes.
*/

//void	bytes_to_map(t_map *map, t_uint pc, t_uint val, t_uint n)
//{
//	int	i;
//
//	i = 0;
//	while (i < n)
//	{
//		set_map(map, pc + i, (val >> (8 * (n - 1 - i))) & 0xFF, );
//		i++;
//	}
//}


/*
** Write value from T_REG, either on a map (T_IND) or to registry (T_REG)
*/

void	i_store(t_map *map, t_proc *pr)
{
	t_uint	val;
	int		i;
	t_uc	cur_val;
	t_uint	cur_pos;

	val = get_reg(pr, pr->args[0].value);
	if (pr->args[1].type == T_REG)
		return set_reg(pr, pr->args[1].value, val);
//	bytes_to_map(map, pr->pc + (pr->args[1].value % IDX_MOD), val, 4);
	// BUG IS HERE
	cur_pos = pr->pc + (pr->args[1].value % IDX_MOD);// This should be added, according to the table: + (pr->args[1].value % IDX_MOD);
	i = 0;
	while (i < 4)
	{
		cur_val = (t_uc)((val >> (8 * (3 - i))) & 0xFF);
		set_map(map, cur_pos + i, cur_val, bot_color_id(map, pr->id));
		i++;
	}
}

void	i_sti(t_map *map, t_proc *pr)
{
	t_uint	val;
	int		i;
	t_uc	cur_val;
	t_uint	cur_pos;

	val = get_reg(pr, pr->args[0].value);
	if (pr->args[1].type == T_REG)
	{
		pr->reg[pr->args[1].value] = val;
		return ;
	}
	cur_pos = pr->pc + pr->cur_ins->codage + (pr->args[1].value % IDX_MOD); // This should be added, according to the table: + (pr->args[1].value % IDX_MOD);
	i = 0;
	while (i < 4)
	{
		cur_val = (t_uc)((val >> (8 * (3 - i))) & 0xFF);
		set_map(map, cur_pos + i, cur_val, bot_color_id(map, pr->id));
		i++;
	}
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
