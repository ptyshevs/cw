/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tk_stringify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:32:59 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/18 13:33:03 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Convert token t_type to static string
*/

char	*tk_type_to_str(t_type type)
{
	if (type == NONE || type == INSTRUCTION)
		return (type == NONE ? "NONE" : "INSTRUCTION");
	else if (type == STRING || type == COMMAND)
		return (type == STRING ? "STRING" : "COMMAND");
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (type == INDIRECT ? "INDIRECT" : "INDIRECT_LABEL");
	else if (type == DIRECT || type == DIRECT_LABEL)
		return (type == DIRECT ? "DIRECT" : "DIRECT_LABEL");
	else if (type == REGISTER || type == LABEL)
		return (type == REGISTER ? "REGISTER" : "LABEL");
	else if (type == SEPARATOR)
		return ("SEPARATOR");
	else if (type == ENDLINE || type == END)
		return (type == ENDLINE ? "ENDLINE" : "END");
	else
		return (NULL);
}

/*
** Convert token t_type to static lowercase string
*/

char	*tk_type_to_lstr(t_type type)
{
	if (type == NONE || type == INSTRUCTION)
		return (type == NONE ? "none" : "instruction");
	else if (type == STRING || type == COMMAND)
		return (type == STRING ? "string" : "command");
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return ("indirect");
	else if (type == DIRECT || type == DIRECT_LABEL)
		return ("direct");
	else if (type == REGISTER || type == LABEL)
		return (type == REGISTER ? "register" : "label");
	else if (type == SEPARATOR)
		return ("separator");
	else if (type == ENDLINE || type == END)
		return (type == ENDLINE ? "endline" : "end");
	else
		return (NULL);
}

/*
** Display tokens of a single line
*/

static void	show_tokens(t_tk *tokens)
{
	while (tokens)
	{
		ft_printf("%s [", tokens->tk);
		ft_printf("%s", tk_type_to_str(tokens->type));
		if (tokens->type == INSTRUCTION)
			ft_printf(tokens->next ? "][%d:%d] [%d]-> " : "][%d:%d] [%d]",
					tokens->line, tokens->chr, tokens->size);
		else
			ft_printf(tokens->next ? "][%d:%d]-> " : "][%d:%d]",
					tokens->line, tokens->chr);
			
		tokens = tokens->next;
	}
	ft_printf("\n");
}

/*
** Test just to see that it works as expected - we have a list of tokens, where
** content of each is another list of tokens of the corresponding line.
*/

void	iter_tokens(t_list *tokens)
{
	while (tokens)
	{
		show_tokens(tokens->content);
		tokens = tokens->next;
	}
}
