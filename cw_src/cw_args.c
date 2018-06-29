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
** Expand codage into an array of types of argument to expect. It takes max. 3
** bytes, since this is max number of arguments allowed.
** There are 4 places for arguments in one codage byte
*/

t_arg	*codage_to_args(const t_op *instr, t_uint codage)
{
	t_arg	*args;
	t_uint	i;

	args = ft_memalloc(sizeof(t_arg) * 4);
	i = 0;
	while (i < 4)
	{
		args[i].code = (t_uc)((codage >> (6 - i * 2)) & 0x3);
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
			return (FALSE);
		i++;
	}
	while (i < 4)
	{
		if (args[i].code != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
** Calculate cumulative size of all arguments
*/

t_uint	args_to_bytes(const t_op *instr, t_arg *args)
{
	t_uint	cum_size;
	t_uint	i;

	cum_size = 0;
	i = 0;
	while (i < instr->nargs)
		cum_size += args[i++].size;
	return (cum_size);
}
