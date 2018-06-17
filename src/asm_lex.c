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
** Validate the file content
** @param content list of lines read from file
*/

t_list	*validate(t_asm *asms, t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines); // and lexical analysis on-the-fly
	if (asms->debug)
		iter_tokens(tokens);
	check_name_comment(tokens);
	check_instructions(tokens); // bad instructions
	// Check name and comment
//	int skip_n_lines = filter_name_comment(tokens);
//	filter_bad_tokens(tokens, skip_n_lines);
	return (tokens);
}
