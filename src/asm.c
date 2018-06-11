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
** Insruction before comment and/or name
*/

void	syntax_error(t_asm *asms, t_list *lines)
{
	(void)asms;
	ft_panic(ft_sprintf("This should not be happening! String that have cause the error: %s\n", lines->content), 2, 1);
}

void	parse_name_comment(t_asm *asms)
{
	t_list	*lines;

	lines = asms->lines;
	while (lines->content && ++asms->line_cnt)
	{
		if (ft_startswith(lines->content, "#") || ft_strispaces(lines->content))
		{
			lines = lines->next;
			continue ;
		}
		else if (ft_strstr(lines->content, NAME_CMD_STRING))
			asms->name = cut_string(asms, &lines, NAME_CMD_STRING);
		else if (ft_strstr(lines->content, COMMENT_CMD_STRING))
			asms->comment = cut_string(asms, &lines, COMMENT_CMD_STRING);
		else
			syntax_error(asms, lines);
		if (asms->name && asms->comment)
			break ;
		lines = lines->next;
	}
}



int main(int ac, char **av)
{
	t_asm	asms;
	asms = parse_cli(ac, av);
	open_files(&asms);
	read_file(asms.fd_from, &asms.lines);
//	lexical_analysis(asms.lines);
	parse_name_comment(&asms);
	ft_printf("name: %s\ncomment: %s\n", asms.name, asms.comment);
	wrap_up(&asms);
}
