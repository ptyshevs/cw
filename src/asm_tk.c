/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:03:38 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/11 19:03:44 by ptyshevs         ###   ########.fr       */
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
	token->chr = start + 1;
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
	t_tk	*tmp;

	while (tokens)
	{
		tmp = tokens->content;
		ft_printf("%s [%d:%d]-> ", tmp->tk, tmp->line, tmp->chr);
		tokens = tokens->next;
	}
	ft_printf("NULL\n");
}

/*
** Transform list of lines read into list of tokens for further analysis
*/

t_list	*tokenize(t_list *lines)
{
	t_list	*tokens;
	int		line_count;

	tokens = NULL;
	line_count = 0;
	while (lines && ++line_count)
	{
		ft_lstappend(&tokens, ft_lstnew(line_to_tk(lines->content, line_count),
										sizeof(t_list)));
		lines = lines->next;
	}
	return (tokens);
}

/*
** Test just to see that it works as expected - we have a list of tokens, where
** content of each is another list of tokens of the corresponding line.
*/

void	iter_tokens(t_list *tokens)
{
	while (tokens)
	{
		show_tokens(tokens->content);
		tokens = tokens->next;
	}
}