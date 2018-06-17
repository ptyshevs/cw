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

void	check_name_comment(t_list *tokens)
{
	t_bool	name_found;
	t_bool	comment_found;
	t_tk	*tmp;

	name_found = FALSE;
	comment_found = FALSE;
	tmp = NULL;
	while (tokens)
	{
		tmp = tokens->content;
		if (!(tmp->type == COMMAND))
			syntax_error(tmp->tk, tk_type_to_str(tmp->type),
						 tmp->line, tmp->chr);
		tmp = tmp->next;
		if (tmp->type != STRING)
			syntax_error(tmp->tk, tk_type_to_str(tmp->type), tmp->line, tmp->chr);
		if (ft_strequ(tmp->tk, NAME_CMD_STRING))
			name_found = TRUE;
		else
			comment_found = TRUE;
		if (name_found && comment_found)
			break ;
		tokens = tokens->next;
	}
	if (tmp->next->type != ENDLINE)
		syntax_error(tmp->tk, tk_type_to_str(tmp->type), tmp->line, tmp->chr);

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
**  Check if tokens of type INSTRUCTION are of a valid type
** @param tokens
*/

void	check_instructions(t_list *tokens)
{
	t_tk	*tmp;

	while (tokens)
	{
		tmp = tokens->content;
		while (tmp)
		{
			if (tmp->type == INSTRUCTION && !is_valid_instruction(tmp))
				instruction_error(tmp->tk, tmp->line, tmp->chr);
			tmp = tmp->next;
		}
		tokens = tokens->next;
	}
}
