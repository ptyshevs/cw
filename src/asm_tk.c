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
** Dispatch token according to their type
** @param line      current line being processed
** @param lines     pointer to the current line in the list of lines
** @param i         index from which to start parsing
** @param line_nbr  line number
** @return NULL if token type is not recognized, otherwise token (t_tk *)
*/

static t_tk	*token_dispatcher(char *line, t_list **lines, int *i, int *line_nbr)
{
	if (line[*i] == '"')
		return (cut_string(lines, i, line_nbr));
	else if (line[*i] == '%' && line[*i + 1] == LABEL_CHAR)
		return (cut_direct_label(line, i, *line_nbr));
	else if (line[*i] == '%')
		return (cut_direct(line, i, *line_nbr));
	else if (line[*i] == 'r' && is_register(line, *i))
		return (cut_register(line, i, *line_nbr));
	else if (line[*i] == SEPARATOR_CHAR)
		return (cut_separator(line, i, *line_nbr));
	else if (line[*i] == '.')
		return (cut_spec(line, i, *line_nbr));
	else if (line[*i] == LABEL_CHAR)
		return (cut_indirect_label(line, i, *line_nbr));
	else if (is_indirect(line, *i))
		return (cut_indirect(line, i, *line_nbr));
	else if (is_label(line, *i, *line_nbr))
		return (cut_label(line, i, *line_nbr));
	else
		return (cut_instruction(line, i, *line_nbr));
}

/*
** Convert line at the top of the list to the list of tokens.
** Passing list of lines by pointer to be able to process multiline strings
*/

static t_tk	*line_to_tk(t_list **lines, int *line_nbr)
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
		if (token)
			tk_append(&tokens, token);
		i += line[i] ? 1 : 0; // so you don't miss nul-terminator
	}
	if (tokens)
	{
		token = create_token(NULL, *line_nbr, i + 1, (*lines)->next ? ENDLINE: END);
		tk_append(&tokens, token);
	}
	return (tokens);
}

/*
** Transform list of lines read into list of tokenized lines, validating
** lexicon on-the-fly.
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
		if (tk)
			ft_lstappend(&tokens, ft_lstnew(tk, sizeof(t_tk)));
		ft_memdel((void **)&tk);
		lines = lines->next;
	}
	return (tokens);
}
