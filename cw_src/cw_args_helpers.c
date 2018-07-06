/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_args_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 23:49:05 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/06 23:50:11 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

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

/*
** Argument type string representation
*/

char	*arg_to_str(t_uc type)
{
	if (type == T_REG)
		return ("T_REG");
	else if (type == T_DIR)
		return ("T_DIR");
	else if (type == T_IND)
		return ("T_IND");
	else if (type == 0)
		return ("T_NAN");
	else
		return ("Unrecognized");
}
