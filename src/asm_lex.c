/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 22:42:46 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/10 22:42:58 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Output a lexical error message for token and exit appropriatedly
*/

void	lexical_error_tk(t_tk *tk, int i)
{
	ft_dprintf(2, "Lexical error at [%d:%d]\n", tk->line, tk->chr + i);
	exit (1);
}

void	lexical_error(int line, int chr)
{
	ft_dprintf(2, "Lexical error at [%d:%d]\n", line, chr);
	exit(1);
}



/*
** Check characters, labels, and tokens
** @param content list of lines read from file
*/

t_list	*lexical_analysis(t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines);
	check_instructions(tokens);
	// Check name and comment
//	int skip_n_lines = filter_name_comment(tokens);
//	filter_bad_tokens(tokens, skip_n_lines);
	return (tokens);
}
