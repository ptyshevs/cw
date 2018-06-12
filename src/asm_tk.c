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

t_tk	*create_token(char *tk, int line_pos, int chr_pos, t_type type)
{
	t_tk	*token;

	token = ft_memalloc(sizeof(t_tk));
	token->tk = tk;
	token->line = line_pos;
	token->chr = chr_pos;
	token->type = type;
	return (token);
}

/*
** Cut token starting from *i position, recording it into a structure
*/

t_tk	*cut_token(t_list **lines, char *line, int *i, int *line_nbr)
{
	int		start;
	t_tk	*token;

	token = ft_memalloc(sizeof(t_tk));
	start = *i;
	*i += 1;
	if (line[start] == '"')
	{
//		cut_string(lines,)
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
	token->line = *line_nbr;
	token->chr = start + 1;
	return (token);
}

/*
** Convert line at the top of the list to the list of tokens.
** Passing list of lines by pointer to be able to process multiline strings
*/

t_tk	*line_to_tk(t_list **lines, int *line_nbr)
{
	char	*line;
	t_tk	*tokens;
	t_tk	*token;
	int		i;

	tokens = NULL;
	line = (*lines)->content;
	i = 0;
	while (line[i])
	{
		token = NULL;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i] || line[i] == COMMENT_CHAR) // consider another comment symbol ';'
			break ;
//		token = cut_token(lines, line, &i, line_nbr);
		if (line[i] == '"')
			token = cut_string(lines, line_nbr, &i);
		line = (*lines)->content;
		tk_append(&tokens, token);
		i += line[i] ? 1 : 0; // so you don't miss nul-terminator
	}
	return (tokens);
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
		tk = line_to_tk(&lines, &line_count);
		ft_lstappend(&tokens, ft_lstnew(tk, sizeof(t_tk)));
		lines = lines->next;
	}
	return (tokens);
}

/*
** Display tokens of a single line
*/

void	show_tokens(t_tk *tokens)
{
	while (tokens)
	{
		ft_printf("%s [", tokens->tk);
		if (tokens->type == NONE)
			ft_printf("NONE");
		else if (tokens->type == INSTRUCTION)
			ft_printf("INSTRUCTION");
		else if (tokens->type == STRING)
			ft_printf("STRING");
		else if (tokens->type == INDIRECT)
			ft_printf("INDIRECT");
		else if (tokens->type == DIRECT)
			ft_printf("DIRECT");
		else if (tokens->type == REGISTER)
			ft_printf("REGISTER");
		else if (tokens->type == LABEL)
			ft_printf("LABEL");
		else if (tokens->type == SEPARATOR)
			ft_printf("SEPARATOR");
		else if (tokens->type == INDIRECT_LABEL)
			ft_printf("INDIRECT_LABEL");
		else if (tokens->type == DIRECT_LABEL)
			ft_printf("DIRECT_LABEL");
		ft_printf("][%d:%d]-> ", tokens->line, tokens->chr);
		tokens = tokens->next;
	}
	ft_printf("NULL\n");
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
