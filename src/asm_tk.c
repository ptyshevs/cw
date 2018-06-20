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

static t_tk	*line_to_tk(t_list **lines, int *line_nbr, t_bool *end_placed)
{
	char	*line;
	t_tk	*tokens;
	t_tk	*tk;
	int		i;

	tokens = NULL;
	line = (*lines)->content;
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i] || line[i] == COMMENT_CHAR || line[i] == ';')
			break ;
		tk = token_dispatcher(line, lines, &i, line_nbr);
		line = (*lines)->content;
		if (tk)
			tk_append(&tokens, tk);
		i += line[i] ? 1 : 0;
	}
	*end_placed = tokens && !(*lines)->next ? TRUE : *end_placed;
	if (tokens)
		tk_append(&tokens, create_token(NULL, *line_nbr, i + 1, (*lines)->next ?
																ENDLINE : END));
	return (tokens);
}

/*
** Transform list of lines read into list of tokenized lines, validating
** lexicon on-the-fly.
*/

t_list		*tokenize(t_list *lines)
{
	t_list	*tokens;
	t_tk	*tk;
	t_bool	end_placed;
	int		line_count;

	end_placed = FALSE;
	tokens = NULL;
	line_count = lines ? 0 : 1;
	while (lines && ++line_count)
	{
		tk = line_to_tk(&lines, &line_count, &end_placed);
		if (tk)
			ft_lstappend(&tokens, ft_lstnew(tk, sizeof(t_tk)));
		ft_memdel((void **)&tk);
		lines = lines->next;
	}
	if (!end_placed)
	{
		tk = create_token(NULL, line_count, 1, END);
		ft_lstappend(&tokens, ft_lstnew(tk, sizeof(t_tk)));
		ft_memdel((void **)&tk);
	}
	return (tokens);
}
