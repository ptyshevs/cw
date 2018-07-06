/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:52:36 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/29 14:52:58 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Convert argument code to type
*/

static t_uc	code_to_type(t_uc code)
{
	if (code == REG_CODE)
		return (T_REG);
	else if (code == DIR_CODE)
		return (T_DIR);
	else if (code == IND_CODE)
		return (T_IND);
	else if (code == 0)
		return (0);
	else
		return (code);
}

/*
** Collect argument that consists of <size> bytes, starting from <pc> position,
** optionally skipping <frwd> bytes.
*/

t_uint	collect_arg(t_map *map, t_uint size, t_uint pc, t_uint frwd)
{
	t_uint	nbr;
	t_uint	i;

	nbr = 0;
	if (size == 0)
		return (nbr);
	i = 0;
	while (i < size)
		nbr = (nbr << 8) + get_map(map, pc + frwd + i++);
	return (nbr);
}

/*
** Expand codage into an array of types of argument to expect. It takes max. 3
** bytes, since this is max number of arguments allowed.
** There are 4 places for arguments in one codage byte
*/

t_arg	*codage_to_args(t_map *map, t_proc *pr, const t_op *instr, t_uint codage)
{
	t_arg	*args;
	t_uint	i;
	t_uint	cum_frwd;

	args = ft_memalloc(sizeof(t_arg) * 4);
	i = 0;
	cum_frwd = 2; // skipping codage
	while (i < 4)
	{
		args[i].code = (t_uc)((codage >> (6 - i * 2)) & 0x3);
		args[i].type = code_to_type(args[i].code);
		if (args[i].type == T_DIR)
			args[i].size = (t_uc)instr->label_size;
		else
			args[i].size = (t_uc)(args[i].type == T_REG ? 1 : 2);
		args[i].value = collect_arg(map, args[i].size, pr->pc, cum_frwd);
		if (args[i].size == 2)
			args[i].value = (short)args[i].value;
		cum_frwd += args[i].size;
		i++;
	}
	return (args);
}

/*
** Unambiguously extend instruction without codage
*/

t_arg	*instr_to_args(t_map *map, t_proc *pr, const t_op *instr)
{
	t_arg	*args;
	t_uint	i;

	args = ft_memalloc(sizeof(t_arg) * 4);
	args[0].type = (t_uc)instr->args[0];
	args[0].size = (t_uc)(args[0].type == T_DIR ? instr->label_size : args[0].type);
	if (args[0].type == T_REG)
		args[0].code = REG_CODE;
	else if (args[0].type == T_DIR)
		args[0].code = DIR_CODE;
	else if (args[0].type == T_IND)
		args[0].code = IND_CODE;
	args[0].value = collect_arg(map, args[0].size, pr->pc, 1);
	if (args[0].size == 2)
		args[0].value = (short)args[0].value;
	i = 1;
	while (i < 4)
	{
		args[i].code = 0;
		args[i].type = code_to_type(args[i].code);
		args[i].size = (t_uc)(args[i].type == T_DIR ?
							instr->label_size : args[i].type);
		i++;
	}
	return (args);
}

/*
** Check if arguments are of valid type
** Check if places for codes that weren't used are zeros.
*/

t_bool	args_are_valid(const t_op *instr, t_arg *args)
{
	t_uint		i;

	i = 0;
	while (i < instr->nargs)
	{
		if (!(args[i].type & instr->args[i]))
			return (False);
		else if (args[i].type == T_REG &&
				(args[i].value == 0 || args[i].value > 16))
			return (False);
		i++;
	}
	return (True);
}
