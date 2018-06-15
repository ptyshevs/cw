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



int main(int ac, char **av)
{
	t_asm	asms;
	asms = parse_cli(ac, av);
	open_files(&asms);
	read_file(asms.fd_from, &asms.lines);
	t_list *tokens = validate(asms.lines);

//	parse_name_comment(&asms);
//	ft_printf("name: %s\ncomment: %s\n", asms.name, asms.comment);
	release_tokens(&tokens);
	wrap_up(&asms);
}
