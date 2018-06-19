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
** Calculate size of the instruction, which is the sum of the following:
**
** 1 byte for opcode (index number of t_op in op_tab)
** 1 byte for codage (if it exists)
** Arguments:
**   - T_REG - 1 byte
**   - T_DIR - 2 or 4 bytes, which depend on label_size of t_op)
**   - T_IND - 4 bytes
*/

void	rec_instr_size(t_tk *instr, const t_op *op)
{
	t_tk		*tmp;
	
	instr->size = REG_CODE;
	op = find_instruction(instr);
	if (op->codage)
		instr->size += REG_CODE;
	tmp = instr;
	while ((tmp = tmp->next)) // what if tmp doesn't exist? Segfault
	{
		instr->size += tmp->size == T_DIR ? op->label_size : tmp->size;
		tmp = tmp->next;
	}
}

/*
** Calculate codage and collect it in the valiable
*/

void	rec_codage(t_tk *instr, t_op *op)
{
	t_tk	*tmp;

	if (!op->codage)
		return ;
	tmp = instr;
	while ((tmp = tmp->next))
	{
		instr->codage = (instr->codage << 2);
		if (tmp->size == T_REG)
			instr->codage += REG_CODE;
		else if (tmp->size == T_DIR)
			instr->codage += DIR_CODE;
		else
			instr->codage += IND_CODE;
		tmp = tmp->next; // skip separator
	}
	instr->codage <<= 2;
	ft_printf("Instruction: %s | Codage: %02X\n", instr->tk, instr->codage);
}
