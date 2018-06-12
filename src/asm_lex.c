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

void	filter_bad_tokens(t_list *tokens)
{
	t_list	*line;
	t_tk	*tk;
	char	*token;
	int		i;

	while (tokens)
	{
		line = tokens->content;
		while (line)
		{
			tk = line->content;
			token = tk->tk;
			i = 0;
			while (token[i])
			{
				if (!ft_strchr(CHAR_SET, token[i]))
					lexical_error(tk, i);
				i++;
			}
			line = line->next;
		}
		tokens = tokens->next;
	}
}

/*
** Filter name and comment section
** @param tokens list of tokenized strings
** @return number of lines to be skipped for instruction validation
*/

int		filter_name_comment(t_list *tokens)
{
	return (0);
}

/*
** Check characters, labels, and tokens
** @param content list of lines read from file
*/

void	lexical_analysis(t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines);
//		iter_tokens(tokens);
	// Check name and comment
	int skip_n_lines = filter_name_comment(tokens);
	filter_bad_tokens(tokens);
}
