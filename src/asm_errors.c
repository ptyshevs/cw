/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 20:08:20 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/14 20:08:31 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Output a lexical error message for token and exit appropriatedly
*/

void	lexical_error(int line, int chr)
{
	ft_dprintf(1, "Lexical error at [%d:%d]\n", line, chr);
	exit(1);
}

/*
** Insruction before comment and/or name
*/

void	syntax_error(char *token, char *type, int line, int chr)
{
	if (!ft_strequ(type, "ENDLINE"))
		ft_dprintf(1, "Syntax error at token [TOKEN][%03d:%03d] %s \"%s\"\n",
					line, chr, type, token);
	else
		ft_dprintf(1, "Syntax error at token [TOKEN][%03d:%03d] %s\n",
					line, chr, type);
	exit(1);
}

/*
** Instruction wasn't found in the list of valid instructions
** (static t_op structure). Output error and exit
*/

void	instruction_error(char *instruction, int line, int chr)
{
	ft_dprintf(1, "Invalid instruction at token [TOKEN][%03d:%03d] INSTRUCTION "
	"\"%s\"", line, chr, instruction);
	exit(1);
}

/*
** Wrapper around ft_dprintf to output formatted error and exit
*/

void	error(int exit_value, char *format, ...)
{
	va_list	va;

	va_start(va, format);
	ft_vdprintf(2, format, va);
	exit(exit_value);
}
