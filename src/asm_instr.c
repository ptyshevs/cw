/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:06:07 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/18 13:06:21 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Find t_op instruction that corresponds to the t_tk *token.
** @param instr token of INSTRUCTION type
** @return pointer to t_op structure, otherwise NULL
*/

const t_op	*find_instruction(t_tk *instr)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, instr->tk))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}
