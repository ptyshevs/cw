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
** Move process <pr> <n> cells forward on a circular memory.
*/

void	move_proc(t_proc *pr, t_uint n)
{
	pr->pc = (pr->pc + n) % MEM_SIZE;
}

/*
** Convert argument code to type
*/

t_uc	code_to_type(t_uc code)
{
	if (code == REG_CODE)
		return (T_REG);
	else if (code == DIR_CODE)
		return (T_DIR);
	else if (code == IND_CODE)
		return (T_IND);
	else
		return (0);
}

/*
** Expand codage into an array of types of argument to expect. It takes max. 3
** bytes, since this is max number of arguments allowed.
*/

t_arg	*codage_to_args(const t_op *instr, t_uint codage)
{
	t_arg	*args;
	int		i;

	args = ft_memalloc(sizeof(t_arg) * instr->nargs);
	if (codage & 0x3) // skip the instruction, don't exit when invalid
		ft_panic(1, "Bad codage: %02X\n", codage);
	i = 0;
	while (i < instr->nargs)
	{
		args[i].code = (t_uc)((codage >> (6 - i * 2)) & 0x3);
		args[i].type = code_to_type(args[i].code);
		args[i].size = (t_uc)(args[i].type == T_DIR ? instr->label_size : args[i].type);
		i++;
	}
	return (args);
}

/*
** Check if arguments are of valid type
*/

t_bool	args_are_valid( const t_op *instr, t_uc *args)
{
	int		i;

	i = 0;
	while (i < instr->nargs)
	{
		if (!(code_to_type(args[i]) & instr->args[i]))
			return (ft_memrelease((void **)&args));
		else
			ft_printf("arg is valid\n");
		i++;
	}
	return (args);
}

/*
** Execute command on which the process currently positioned
*/

void	exec(t_map *map, t_proc *pr)
{
	const t_op	*instr;
	t_arg		*args;

	ft_printf("Opcode: %02X\n", map->map[pr->pc]);
	instr = find_instr(map->map[pr->pc]);
	if (instr && instr->codage) // where to store instruction execution state?
	{
		args = codage_to_args(instr, map->map[pr->pc + 1]);
		if (!(args = validate_args(codage_to_arg(instr, map->map[pr->pc + 1]), instr)))
			move_proc(pr, 1);

		show_args(args);
		// jump right after where the instructions have finished
	}
	else
		move_proc(pr, 1);
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
	show_procs(map.procs);
	exec(&map, map.procs);
	return (0);
}
