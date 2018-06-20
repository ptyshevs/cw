/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 12:27:58 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 12:30:14 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/*
** ASM-like compiler
*/

int main(int ac, char **av)
{
	t_asm	asms;
	t_list	*tokens; // used on compilation step

	asms = parse_cli(ac, av);
	open_files(&asms);
	read_file(asms.fd_from, &asms.lines);
	tokens = validate(&asms, asms.lines);
	if (asms.flags & DEBUG)
		iter_tokens(tokens);
	if (asms.flags & DUMP_STDOUT)
		dump_to_stdout(&asms, tokens);
	else
		write_file(&asms, tokens);
	release_tokens(&tokens);
	wrap_up(&asms);
}
