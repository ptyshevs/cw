/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 17:06:05 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/29 17:06:19 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Find t_op instruction by its <op>
*/

const t_op	*find_instr(t_uint op)
{
	if (op == 0 || op > 16)
		return (NULL);
	else
		return (&g_op_tab[op - 1]);
}

/*
** After the instruction was executed, clean-up proc fields
*/

void	wrap_up(t_map *map, t_proc *pr)
{
	if (pr->cur_ins->op == 9 && pr->jumped)
		pr->jumped = False;
	else
		move_proc(map, pr, args_to_bytes(pr->cur_ins, pr->args) +
			pr->cur_ins->codage + 1);
	ft_memdel((void **)&pr->args);
	pr->cur_ins = NULL;
	pr->cur_cycle = 0;
}

/*
** Activate function if charging period has ended.
** Arguments are read regardless of whether there is codage or not
*/

void	activate_instr(t_map *map, t_proc *pr)
{
	static void (*functions[16])(t_map *, t_proc *)={i_live, i_load, i_store,
		i_add, i_sub, i_and, i_or, i_xor, i_zjmp, i_ldi, i_sti, i_fork, i_lload,
		i_lldi, i_lfork, i_aff};

	if (pr->cur_ins->codage)
		pr->args = codage_to_args(map, pr, pr->cur_ins, get_map(map, pr->pc + 1));
	else // if no codage
		pr->args = instr_to_args(map, pr, pr->cur_ins);
	log_instruction(map, pr);
	if (!args_are_valid(pr->cur_ins, pr->args))
	{
//		to_log(map, "Invalid arguments for instruction %s\n", pr->cur_ins->name);
		return ;
	}
	log_map(map, pr, "Activating function");
	(*functions[pr->cur_ins->op - 1])(map, pr);
	log_reg(map, pr);
}

/*
** Execute command on which the process currently positioned
*/

void	exec(t_map *map, t_proc *pr)
{
	if (!pr->cur_ins) // read instruction and start charging
	{
		if (!(pr->cur_ins = find_instr(get_map(map, pr->pc)))) // invalid instruction
			return move_proc(map, pr, 1); // move forward
	}
	if (pr->cur_cycle < pr->cur_ins->cycles) // charge
	{
		pr->cur_cycle++;
		log_map(map, pr, "Charging %d/%d", pr->cur_cycle, pr->cur_ins->cycles);
	}
	if (pr->cur_cycle == pr->cur_ins->cycles)
	{
		activate_instr(map, pr);
		wrap_up(map, pr);
	}
}

/*
** Update all processes
*/

void	update_procs(t_map *map)
{
	t_proc	*pr;

	pr = map->procs;
	while (pr)
	{
		exec(map, pr);
		pr = pr->next;
	}
}
