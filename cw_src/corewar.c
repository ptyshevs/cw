/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 13:25:34 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 13:25:56 by ptyshevs         ###   ########.fr       */
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
	move_proc(pr, args_to_bytes(pr->cur_ins, pr->cur_args) + 1);
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
	else
		pr->cur_args = instr_to_args(pr->cur_ins);
	if (!args_are_valid(pr->cur_ins, pr->cur_args))
	{
		log_map(map, pr, "Invalid arguments for instruction");
		move_proc(pr, 1);
	}
	show_args(pr->cur_args);
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
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;

	map.log.level = v_none;
	map.log.to = 1;
	parse_cli(&map, ac, av);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_none)
	{
//		show_bots(map.bots, map.n_bots);
//		show_map(&map);
	}
//	show_procs(map.procs);
	for (int i = 0; i < 100; ++i)
	{
		exec(&map, map.procs);
	}
	return (0);
}
