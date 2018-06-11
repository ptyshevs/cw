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

void	pass_lines(t_list **lines, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		*lines = (*lines)->next;
		i++;
	}
}

/*
** Parse name. Handle multi-line names
** @param asms
*/

void	parse_name(t_asm *asms, t_list *lines)
{
	ft_printf("parsing name: %s\n", lines->content);
	asms->name = ft_strdup(lines->content);
}

/*
** Cut a comment, start to which is pointed by <comment>. Traverse multiple
** lines if necessary.
*/

char	*cut_comment(char *comment, t_list *lines)
{
	char	*collect;
	char	*tmp;

	if (ft_strchr(comment, '"'))
		return (ft_strtok(comment, "\""));
	collect = ft_strdup(comment);
	lines = lines->next;
	while (lines && !ft_strchr(lines->content, '"'))
	{
		tmp = collect;
		collect = ft_sjoin(3, collect, lines->content, "\n");
		ft_strdel(&tmp);
		lines = lines->next;
	}
	if (!lines) // Non enclosing double-quote
		return (NULL);
	// find closing double-quote
	// calculate distance to it
	size_t len = ft_strchr(lines->content, '"') - (char *)lines->content;
	char *another = ft_strtrunc(lines->content, len, FALSE);
	tmp = collect;
	collect = ft_sjoin(3, collect, "\n", another);
	ft_strdel(&tmp);
	return (collect);
}

char	*ft_strchr_ignore_comments(char *str, char c)
{

}

/*
** Cut string in form "somestring" after a <what> field
*/

char	*cut_string(t_asm *asms, t_list **lines, char *what)
{
	char	*line;
	int		cnt_lines;
	char	*tmp;

	line = (*lines)->content;
	while (*line && ft_isspace(*line))
		line++;
	if (!ft_startswith(line, what))
		return (NULL);
	else
		line += ft_slen(what);
	while (*line && ft_isspace(*line))
		line++;
	if (*line != '"')
		return (NULL);
	line++; // skip opening double-quote
	if (ft_strchr(line, '"') && (tmp = ft_strtok(line, "\"")))
		return (tmp);
	tmp = cut_comment(line, *lines);
	cnt_lines = ft_strcnt(tmp, '\n');
	asms->line_cnt += cnt_lines;
	pass_lines(lines, cnt_lines);
	return (tmp);
}

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


/*
** Read file to list (required to perform preliminary lexical analysis
*/

void	read_file(t_asm *asms)
{
	char	*tmp;

	tmp = NULL;
	while (ft_sgnl(asms->fd_from, &tmp) > 0)
		ft_lstappend(&asms->lines, ft_lstnew(tmp, ft_slen(tmp) + 1));
}

int main(int ac, char **av)
{
	t_asm	asms;
	asms = parse_cli(ac, av);
	open_files(&asms);
	read_file(&asms);
//	lexical_analysis(asms.lines);
	parse_name_comment(&asms);
	ft_printf("name: %s\ncomment: %s\n", asms.name, asms.comment);
	wrap_up(&asms);
}
