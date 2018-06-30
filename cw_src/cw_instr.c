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

void	wrap_up(t_proc *pr)
{
	move_proc(pr, args_to_bytes(pr->cur_ins, pr->cur_args) +
			pr->cur_ins->codage + 1);
	ft_memdel((void **)&pr->cur_args);
	pr->cur_ins = NULL;
	pr->cur_cycle = 0;
}


/*
** Activate function if charging period has ended.
** Arguments are read regardless of whether there is codage or not
*/

void	activate_instr(t_map *map, t_proc *pr)
{
	if (pr->cur_ins->codage)
		pr->cur_args = codage_to_args(pr->cur_ins, get_map(map, pr->pc + 1));
	else // if no codage
		pr->cur_args = instr_to_args(pr->cur_ins);
	if (!args_are_valid(pr->cur_ins, pr->cur_args))
	{
		log_map(map, pr, "Invalid arguments for instruction");
		move_proc(pr, 1);
	}
//	if (map->log.level > v_essential)
//		show_args(pr->cur_args);
	// actual instruction activation should be here
}

/*
** Execute command on which the process currently positioned
*/

void	exec(t_map *map, t_proc *pr)
{
	if (!pr->cur_ins) // read instruction and start charging
	{
		if (!(pr->cur_ins = find_instr(map->map[pr->pc]))) // invalid instruction
			return move_proc(pr, 1); // move forward
	}
	// charging and activation phase
	if (pr->cur_cycle < pr->cur_ins->cycles) // charge
	{
		pr->cur_cycle++;
		log_map(map, pr, "Charging %d/%d", pr->cur_cycle, pr->cur_ins->cycles);
	}
	else // activate and clean-up
	{
		log_map(map, pr, "Activating function");
		activate_instr(map, pr);
		wrap_up(pr);
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
