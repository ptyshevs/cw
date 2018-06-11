/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:05:00 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/11 17:05:19 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Pass <cnt> lines of <lines> list.
*/

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
** Cut a comment, start to which is pointed by <comment>. Traverse multiple
** lines if necessary.
*/

char	*cut_substring(char *comment, t_list *lines)
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
	tmp = cut_substring(line, *lines);
	cnt_lines = ft_strcnt(tmp, '\n');
	asms->line_cnt += cnt_lines;
	pass_lines(lines, cnt_lines);
	return (tmp);
}
