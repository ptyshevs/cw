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

	if (!tk)
		return ;
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
** Dispatch token according to their type
** @param line
** @param lines
** @param i
** @param line_nbr
** @return NULL if token type is not recognized, otherwise token (t_tk *)
*/

t_tk	*token_dispatcher(char *line, t_list **lines, int *i, int *line_nbr)
{
	t_tk	*token;

	token = NULL;
	if (line[*i] == '"')
		token = cut_string(lines, i, line_nbr);
	else if (line[*i] == '%' && line[*i + 1] == LABEL_CHAR)
		token = cut_direct_label(line, i, *line_nbr);
	else if (line[*i] == '%')
		token = cut_direct(line, i, *line_nbr);
	else if (line[*i] == 'r' && is_register(line, *i))
		return (cut_register(line, i, *line_nbr));
	else if (line[*i] == SEPARATOR_CHAR)
		return (cut_separator(line, i, *line_nbr));
	else if (is_label(line, *i))
		return (cut_label(line, i, *line_nbr));
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
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i] || line[i] == COMMENT_CHAR) // consider another comment symbol ';'
			break ;
		token = token_dispatcher(line, lines, &i, line_nbr);
		line = (*lines)->content; // need to jump after multiline STRING processing
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
