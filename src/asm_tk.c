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
		while (line[*i] && line[*i] != '"')
			*i += 1;
		if (line[*i] == '"')
			token->tk = ft_strtrunc(&(line[start]), *i + 1 - start, FALSE);
	}
	else
		while (line[*i] && !ft_isspace(line[*i]) && !ft_strchr(",", line[*i]))
			*i += 1;
	if (!token->tk)
		token->tk = ft_strtrunc(&(line[start]), (size_t)(*i - start), FALSE);
	token->line = line_nbr;
	token->chr = start + 1;
	return (token);
}

/*
** Append line tokens to the list of tokens
*/

void	tk_append(t_tk **atokens, t_tk *tk)
{
	t_tk	*tmp;

	if (!*atokens)
		*atokens = tk;
	else
	{
		tmp = *atokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tk;
	}
}

/*
** Convert line to the list of tokens. Should the spaces be ignored?
*/

t_tk	*line_to_tk(char *line, int line_nbr)
{
	t_tk	*tokens;
	t_tk	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i] || line[i] == COMMENT_CHAR) // consider another comment symbol ';'
			break ;
		token = cut_token(line, &i, line_nbr);
		tk_append(&tokens, token);
		if (line[i])
			i++;
	}
	return (tokens);
}

void	show_tokens(t_tk *tokens)
{
	while (tokens)
	{
		ft_printf("%s [%d:%d]-> ", tokens->tk, tokens->line, tokens->chr);
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
	t_tk	*tk;
	int		line_count;

	tokens = NULL;
	line_count = 0;
	while (lines && ++line_count)
	{
		tk = line_to_tk(lines->content, line_count);
		ft_lstappend(&tokens, ft_lstnew(tk, sizeof(t_tk)));
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
