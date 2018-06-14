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

void	bad_instruction(t_tk *tk)
{
	ft_dprintf(2, "Invalid instruction at token [TOKEN][%03d:%03d] INSTRUCTION "
	"\"%s\"", tk->line, tk->chr, tk->tk);
	exit(1);
}

/*
** Check if the instruction is in the instruction set
*/

t_bool	is_valid_instruction(t_tk *tmp)
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
				bad_instruction(tmp);
			tmp = tmp->next;
		}
		tokens = tokens->next;
	}
}
