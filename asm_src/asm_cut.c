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

static void	pass_lines(t_list **lines, int cnt)
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

static char	*cut_substring(char *start, t_list *lines)
{
	char	*collect;
	char	*tmp;
	char	*another;
	size_t	len;

	collect = ft_strdup(start);
	lines = lines->next;
	while (lines && !ft_strchr(lines->content, '"'))
	{
		tmp = collect;
		collect = ft_sjoin(3, collect, lines->content, "\n");
		ft_strdel(&tmp);
		lines = lines->next;
	}
	if (!lines)
		return (NULL);
	len = ft_strchr(lines->content, '"') - (char *)lines->content;
	another = ft_strtrunc(lines->content, len + 1, FALSE);
	tmp = collect;
	collect = ft_sjoin(3, collect, "\n", another);
	ft_strdel(&tmp);
	ft_strdel(&another);
	return (collect);
}

/*
** Cut string token, from <start>.
**
** Start should be index of the opening double quote.
*/

t_tk		*cut_string(t_list **lines, int *start, int *line_nbr)
{
	int		cnt_lines;
	char	*tmp;
	char	*more;
	t_tk	*token;

	tmp = (*lines)->content;
	if ((more = ft_strchr(&(tmp[*start + 1]), '"')))
		tmp = ft_strsub(tmp, *start, more - tmp - *start + 1);
	else
		tmp = cut_substring(&(tmp[*start]), *lines);
	if (!tmp)
		ft_panic(1, "No closing bracket found for STRING token [%d:%d] %s\n",
				*line_nbr, *start, &(((char *)(*lines)->content)[*start]));
	cnt_lines = ft_strcnt(tmp, '\n');
	*line_nbr += cnt_lines;
	pass_lines(lines, cnt_lines);
	token = create_token(tmp, *line_nbr - cnt_lines, *start + 1, STRING);
	if (!ft_strchr(token->tk, '\n'))
		*start += ft_slen(token->tk) - 1;
	else
	{
		more = ft_strrchr(token->tk, '\n') + 1;
		*start = ft_slen(more) - 1;
	}
	return (token);
}

/*
** Cut direct label
*/

t_tk		*cut_direct_label(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = *start + 1;
	while (line[++i])
	{
		if (ft_isspace(line[i]) || line[i] == SEPARATOR_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, line[i]))
			lexical_error(line_nbr, i + 1);
	}
	if (ft_slen(tk = ft_strtrunc(&(line[*start]), i - *start, FALSE)) == 2)
		lexical_error(line_nbr, *start + 1);
	token = create_token(tk, line_nbr, *start + 1, DIRECT_LABEL);
	*start = i - 1;
	return (token);
}

/*
** Cut direct value that starts from DIRECT_CHAR (%)
** @param line being processed
** @param start index of token start (so line[*i] == DIRECT_CHAR)
** @param line_nbr line order
** @return New token of DIRECT type
*/

t_tk		*cut_direct(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = *start;
	while (line[++i])
	{
		if (i == *start + 1 && line[i] == '-')
			continue;
		else if (ft_isspace(line[i]) || line[i] == SEPARATOR_CHAR)
			break ;
		else if (!ft_isdigit(line[i]))
		{
			if (!ft_strchr(LABEL_CHARS, line[i]))
				lexical_error(line_nbr, i + 1);
			break ;
		}
	}
	if (ft_slen(tk = ft_strtrunc(&(line[*start]), i - *start, FALSE)) == 1)
		lexical_error(line_nbr, i);
	token = create_token(tk, line_nbr, *start + 1, DIRECT);
	*start = i - 1;
	return (token);
}
