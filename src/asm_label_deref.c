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

void	rec_codage(t_tk *instr, const t_op *op)
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
}

/*
** Find label instruction offset
*/

int		find_label(t_list *tokens, t_tk *label_param, char *label)
{
	t_tk	*tk;
	int		size;

	size = 0;
	while (tokens)
	{
		tk = tokens->content;
		while (tk)
		{
			if (tk->type == LABEL && ft_strequ(tk->tk, label))
				return (size);
			if (tk->type == INSTRUCTION)
				size += tk->size;
			tk = tk->next;
		}
		tokens = tokens->next;
	}
	label_error(label_param, label);
	return (size);
}

/*
** Replace label with its direct-indirect value
*/

void	replace_label(t_list *tokens, t_tk *label_param, int cum_size)
{
	int		size_to;
	char	*to_label_format;
	char	*value;

	to_label_format = ft_strjoin(label_param->tk +
						(label_param->type == DIRECT_LABEL ? 2 : 1), ":");
	size_to = find_label(tokens, label_param, to_label_format);
	ft_strdel(&to_label_format);
	ft_strdel(&label_param->tk);
	if (label_param->type == DIRECT_LABEL)
		value = ft_sprintf("%%%d", size_to - cum_size);
	else
		value = ft_sprintf("%d", size_to - cum_size);
	label_param->tk = value;
	label_param->type = label_param->type == DIRECT_LABEL ? DIRECT : INDIRECT;
}

/*
** Store counter of total byte offset and resolve any label encountered by
** replacing it with a value
*/

void	label_deref(t_list *tokens)
{
	t_list			*tmp;
	t_tk			*tk;
	int				cum_size;
	t_tk			*instr;

	cum_size = 0;
	tmp = tokens;
	while (tmp)
	{
		instr = NULL;
		tk = tmp->content;
		while (tk)
		{
			if (tk->type == DIRECT_LABEL || tk->type == INDIRECT_LABEL)
				replace_label(tokens, tk, cum_size);
			if (tk->type == INSTRUCTION)
				instr = tk;
			if (tk->type == ENDLINE && instr)
				cum_size += instr->size;
			tk = tk->next;
		}
		tmp = tmp->next;
	}
}
