/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_label_deref.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:59:04 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/18 19:59:16 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Store the offset size of an instruction
*/

void	rec_instr_size(t_tk *instr)
{
	t_tk	*tmp;
	
	instr->size = 1;
	if (find_instruction(instr)->codage)
		instr->size += REG_CODE;
	tmp = instr;
	while ((tmp = tmp->next)) // what if tmp doesn't exist? Segfault
	{
		instr->size += tmp->size;
		tmp = tmp->next;
	}
}

/*
 * Calculate codage and collect it in the valiable
 */

void	rec_codage(t_tk *instr)
{
	
}
