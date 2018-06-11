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
** Check characters, labels, and tokens
** @param content list of lines read from file
*/

void	lexical_analysis(t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines);
	iter_tokens(tokens);
}