/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_log_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 23:59:00 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/06 23:59:07 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	log_zjmp(t_map *map, t_proc *pr)
{
	if (pr->carry)
		to_log(map, "P%5d | zjmp %hd OK\n", pr->index,
				get_arg(map, pr, 0, False));
	else
		to_log(map, "P%5d | zjmp %hd FAILED\n", pr->index,
				get_arg(map, pr, 0, False));
}

void	log_fork(t_map *map, t_proc *pr, t_uint new_pc)
{
	if (map->log->level & v_ops)
		to_log(map, "P%5d | %s %d (%u)\n", pr->index, pr->cur_ins->name,
			pr->args[0].value, new_pc);
}

void	log_args(t_map *map, t_proc *pr)
{
	if (!(map->log->level & v_args))
		return ;
	if (pr->cur_ins->nargs == 1)
		to_log(map, "P%5d | %s\n", pr->index, arg_to_str(pr->args[0].type));
	else if (pr->cur_ins->nargs == 2)
		to_log(map, "P%5d | %s %s\n", pr->index, arg_to_str(pr->args[0].type),
			arg_to_str(pr->args[1].type));
	else
		to_log(map, "P%5d | %s %s %s\n", pr->index,
			arg_to_str(pr->args[0].type), arg_to_str(pr->args[1].type),
			arg_to_str(pr->args[2].type));
}

/*
** Log instruction and its artuments
*/

void	log_instruction(t_map *map, t_proc *pr)
{
	char	*tmp;
	t_uint	i;

	if (!(map->log->level & v_ops))
		return ;
	if (pr->cur_ins->op == 9)
		return (log_zjmp(map, pr));
	else if (pr->cur_ins->op == 12 || pr->cur_ins->op == 15 ||
			pr->cur_ins->op == 11)
		return ;
	tmp = ft_sprintf("P%5d | %s", pr->index, pr->cur_ins->name);
	i = 0;
	while (i < pr->cur_ins->nargs)
	{
		tmp = ft_concat(tmp, ft_sprintf(
				(pr->args[i].type == T_REG ? " r%d" : " %d"),
				pr->args[i].value), True);
		i++;
	}
	to_log(map, "%s\n", tmp);
	ft_strdel(&tmp);
}

/*
** Log movement that follows after executing valid instruction
*/

void	log_move(t_map *map, t_proc *pr, t_uint n)
{
	char	*cmb;
	char	*t;
	t_uint	i;

	cmb = NULL;
	i = 0;
	while (i < n)
	{
		t = ft_sprintf(i + 1 < n || map->log->identical ? "%02x " : "%02x",
						get_map(map, pr->pc + i));
		cmb = ft_concat(cmb, t, True);
		i++;
	}
	if (pr->pc == 0)
		to_log(map, "ADV %u (0x0000 -> %#06x) %s\n", n, pr->pc + n, cmb);
	else if (pr->pc + n == 0)
		to_log(map, "ADV %u (%#06x -> 0x0000) %s\n", n, pr->pc, cmb);
	else
		to_log(map, "ADV %u (%#06x -> %#06x) %s\n", n, pr->pc, pr->pc + n, cmb);
	ft_strdel(&cmb);
}
