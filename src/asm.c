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

#include <ft_lst.h>
#include "asm.h"

/*
** Parse name. Handle multi-line names
** @param asms
*/

void	parse_name(t_asm *asms, t_list *lines)
{
	ft_printf("parsing name: %s\n", lines->content);
	asms->name = ft_strdup(lines->content);
}

void	parse_comment(t_asm *asms, t_list *lines)
{
	ft_printf("parsing comment: %s\n", lines->content);
	asms->comment = ft_strdup(lines->content);
}

/*
** Insruction before comment and/or name
*/

void	syntax_error(t_asm *asms, t_list *lines)
{
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
			parse_name(asms, lines);
		else if (ft_strstr(lines->content, COMMENT_CMD_STRING))
			parse_comment(asms, lines);
		else
			syntax_error(asms, lines);
		if (asms->name && asms->comment)
			break ;
		lines = lines->next;
	}
}

/*
** Check characters, labels, and
** @param content list of lines read from file
*/

void	lexical_analysis(t_list *content)
{

}

/*
** Read file to list (required to perform preliminary lexical analysis
*/

void	read_file(t_asm *asms)
{
	char	*tmp;

	tmp = NULL;
	while (ft_usgnl(asms->fd_from, &tmp) > 0)
		ft_lstappend(&asms->lines, ft_lstnew(tmp, ft_slen(tmp) + 1));
}

int main(int ac, char **av)
{
	t_asm	asms;
	t_list	*file_content;
	asms = parse_cli(ac, av);
	open_files(&asms);
	read_file(&asms);
	lexical_analysis(asms.lines);
	parse_name_comment(&asms);
	wrap_up(&asms, &file_content);
}
