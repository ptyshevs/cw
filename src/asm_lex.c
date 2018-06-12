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
** Output a lexical error message and exit appropriatedly
*/

void	lexical_error(t_tk *tk, int i)
{
	ft_dprintf(2, "Lexical error at [%d:%d]\n", tk->line, tk->chr + i);
	exit (1);
}

/*
** Check character set of each token, stop execution on case of any errors
** @param tokens
*/

void	filter_bad_tokens(t_list *tokens, int skip_n_lines)
{
	t_tk	*tk;
	char	*token;
	int		i;

	i = 0;
	while (tokens)
	{
		if (i++ < skip_n_lines)
		{
			tokens = tokens->next;
			continue ;
		}
		tk = tokens->content;
		while (tk)
		{
			token = tk->tk;
			i = 0;
			while (token[i])
			{
				if (!ft_strchr(CHAR_SET, token[i]))
					lexical_error(tk, i);
				i++;
			}
			tk = tk->next;
		}
		tokens = tokens->next;
	}
}

/*
** If anything is after the closing quote, it's lexical error
*/

int		find_endquote(t_tk *tmp, t_list *tokens)
{
	t_bool	startline;
	char	*token;
	int		lines;
	int		i;

	startline = TRUE;
	lines = 0;
	while (tokens)
	{
		token = startline ? tmp->tk : ((t_tk *)tokens->content)->tk;
		i = startline ? 1 : 0;
		while (token[i])
		{
			if (token[i] == '"')
			{
				if (token[i + 1]) // char is after the closing doublequote
					lexical_error(tmp, i + 1);
				else if (tmp->next) // token after the closing doublequote
					lexical_error(tmp->next, 0);
				return (lines);
			}
			i++;
		}
		tokens = tokens->next;
		lines++;
		startline = FALSE;
	}
	ft_dprintf(2, "Something went wrong. You shouldn't be here\n");
	return (lines);
}

/*
** Filter name and comment section
** @param tokens list of tokenized strings
** @return number of lines to be skipped for instruction validation
*/

int		filter_name_comment(t_list *tokens)
{
	t_tk	*tmp;
	int		cnt_lines;

	cnt_lines = 0;
	while (tokens)
	{
		if (tokens->content)
		{
			tmp = tokens->content;
			// what if not .name or .comment?
			if ((ft_strequ(tmp->tk, NAME_CMD_STRING) ||
				ft_strequ(tmp->tk, COMMENT_CMD_STRING)))
			{
				if ((tmp = tmp->next)) // empty string after .comment or .name
				{
					if (!ft_startswith(tmp->tk, "\""))
						lexical_error(tmp, 0);
					int skip_lines = find_endquote(tmp, tokens);
					cnt_lines += skip_lines;
					while (skip_lines--)
						tokens = tokens->next;
				}
			}
			else
				return (cnt_lines);
		}
		tokens = tokens->next;
		cnt_lines++;
	}
	return (cnt_lines);
}

/*
** Check characters, labels, and tokens
** @param content list of lines read from file
*/

void	lexical_analysis(t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines);
	iter_tokens(tokens);
	// Check name and comment
	int skip_n_lines = filter_name_comment(tokens);
	filter_bad_tokens(tokens, skip_n_lines);
}
