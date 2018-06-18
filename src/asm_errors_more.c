/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:29:55 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/18 14:30:16 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Invalid parameter error
*/

void	parameter_error(t_tk *instr, t_tk *param, int pos)
{
	ft_dprintf(1, "Invalid parameter %d type %s for instruction %s\n",
		pos, tk_type_to_lstr(param->type), instr->tk);
	exit(1);
}

/*
** Too small amount of instruction arguments
*/

void	parameter_count_error(t_tk *instr)
{
	ft_dprintf(1, "Invalid parameter count for instruction %s\n", instr->tk);
	exit(1);
}

void	unexpected_eof_error(void)
{
	ft_printf("Syntax error - unexpected end of input "
				"(Perhaps you forgot to end with a newline ?)\n");
	exit(1);
}
