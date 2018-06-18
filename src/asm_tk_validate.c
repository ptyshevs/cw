/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tk_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 19:35:13 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/14 19:35:41 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**  Main file for different validating routines
*/

/*
** Token list must start with the .name COMMAND followed by STRING or
** a .comment COMMAND followed by string. First two tokenized lines should
** contain both.
**
** If any other type of token is met before those two described above, the
** syntax error is rised.
*/

void			check_name_comment(t_asm *asms, t_list *tokens)
{
	t_tk	*tmp;

	tmp = NULL;
	while (tokens && (tmp = tokens->content))
	{
		tmp = tokens->content;
		if (!(tmp->type == COMMAND))
			syntax_error(tmp->tk, tk_type_to_str(tmp->type),
						tmp->line, tmp->chr);
		if (tmp->next && tmp->next->type != STRING)
			syntax_error(tmp->next->tk, tk_type_to_str(tmp->next->type),
						tmp->next->line, tmp->next->chr);
		if (ft_strequ(tmp->tk, NAME_CMD_STRING))
			asms->name = tmp->next->tk;
		else
			asms->comment = tmp->next->tk;
		if (asms->name && asms->comment)
			break ;
		tokens = tokens->next;
	}
	tmp = tmp->next->next; // if there is a segfault, it is here
	if (tmp && tmp->type != ENDLINE)
		syntax_error(tmp->tk, tk_type_to_str(tmp->type), tmp->line, tmp->chr);
}

/*
** Validate the number of arguments
*/

static void		check_arg_amount(t_tk *instr)
{
	const t_op		*op;
	t_tk			*tmp;
	unsigned int	cnt;

	tmp = instr;
	op = find_instruction(tmp);
	cnt = 0;
	while ((tmp = tmp->next))
	{
		if (tmp->type == ENDLINE)
			syntax_error_tk(tmp);
		is_parameter(tmp->type) ? cnt += 1 : syntax_error_tk(tmp);
		if (op && cnt > op->nargs)
			parameter_error(instr, tmp, cnt - 1);
		tmp = tmp->next;
		if (tmp->type == ENDLINE || tmp->type == END)
			break ;
		if ((tmp->type != SEPARATOR))
			syntax_error_tk(tmp);
	}
	if (op && cnt < op->nargs)
		parameter_count_error(instr);
	else if (tmp->type == END) // if there is a segfault, its here
		unexpected_eof_error();
}

/*
** Validate type of the arguments
*/

static void		check_arg_type(t_tk *instr)
{
	t_tk		*tmp;
	const t_op	*op;
	int			i;

	tmp = instr;
	op = find_instruction(tmp);
	i = 0;
	while (i < op->nargs && (tmp = tmp->next))
	{
		if (!(tmp->size & op->args[i]))
			parameter_error(instr, tmp, i);
		tmp = tmp->next;
		i++;
	}
}

/*
** Check if the instruction is in the instruction set
*/

static t_bool	is_valid_instruction(t_tk *tmp)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
	{
		if (ft_strequ(op_tab[i].name, tmp->tk))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
**  Check if tokens of type INSTRUCTION are of a valid type and have right args
** @param tokens List of tokenized lines
*/

void			check_instructions(t_list *tokens)
{
	t_tk	*tmp;

	while (tokens)
	{
		tmp = tokens->content;
		while (tmp)
		{
			if (tmp->type == INSTRUCTION)
			{
				check_arg_amount(tmp);
				if (!is_valid_instruction(tmp))
					instruction_error(tmp->tk, tmp->line, tmp->chr);
				check_arg_type(tmp);
			}
			tmp = tmp->next;
		}
		tokens = tokens->next;
	}
}
