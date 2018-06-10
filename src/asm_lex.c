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

	line_count = 0;
	while (line && ++line_count)
	{
		tk = line_to_tk(line->content, line_count);
		show_tokens(tk);
		line = line->next;
	}
}