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

#include "ft_lst.h"
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
** Cut token into "fresh" string
*/

t_tk	*cut_token(char *line, int *i, int line_nbr)
{
	int		start;
	t_tk	*token;

	token = ft_memalloc(sizeof(t_tk));
	start = *i;
	*i += 1;
	if (line[start] == '"')
	{
		while(line[*i] && line[*i] != '"')
				*i += 1;
		if (line[*i] == '"')
			*i += 1;
	}
	else
		while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr(",", line[*i]))
			*i += 1;
	token->tk = ft_strtrunc(&(line[start]), (size_t) (*i - start), FALSE);
	token->line = line_nbr;
	token->chr = start;
	return (token);
}

/*
** Convert line to the list of tokens. Should the spaces be ignored?
*/

t_list	*line_to_tk(char *line, int line_nbr)
{
	t_list	*tk;
	t_tk	*token;
	int		i;

	tk = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i] || line[i] == COMMENT_CHAR) // consider another comment symbol ';'
			break ;
		token = cut_token(line, &i, line_nbr);
		ft_lstappend(&tk, ft_lstnew(token, sizeof(t_tk)));
		if (line[i])
			i++;
	}
	return (tk);
}

void	show_tokens(t_list *tokens)
{
	while (tokens)
	{
		ft_printf("%s -> ", ((t_tk *)tokens->content)->tk);
		tokens = tokens->next;
	}
	ft_printf("NULL\n");
}

/*
** Check characters, labels, and tokens
** @param content list of lines read from file
*/

void	lexical_analysis(t_list *line)
{
	t_list	*tk;
	int		line_count;

	tk = NULL;
	line_count = 0;
	while (line && ++line_count)
	{
		if (!ft_startswith(line->content, "#") && !ft_strispaces(line->content))
			tk = line_to_tk(line->content, line_count);
		show_tokens(tk);
		line = line->next;
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
	lexical_analysis(asms.lines);
//	parse_name_comment(&asms);
	wrap_up(&asms);
}
