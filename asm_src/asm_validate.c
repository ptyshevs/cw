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
** Check for .name - .comment duplication, optionally cutting tokens if COMMAND
** if after an instruction
** WTF is n_c_i? I'm glad you've asked. It's an array that contains 3 booleans:
** n_c_i[0] - was a name found?
** n_c_i[1] - was a comment found?
** n_c_i[2] - was an instruction found?
*/

void	check_duplicates(t_list *tokens)
{
	t_tk			*tmp;
	static t_bool	n_c_i[3];
	t_list			*prev;

	prev = tokens;
	while (tokens && (tmp = tokens->content))
	{
		while (tmp)
		{
			if (tmp->type == COMMAND)
			{
				if (n_c_i[2])
					return (release_tokens(&prev->next));
				if (ft_strequ(tmp->tk, NAME_CMD_STRING))
					n_c_i[0] = !n_c_i[0] ? True : duplicate_error(tmp);
				else
					n_c_i[1] = !n_c_i[1] ? True : duplicate_error(tmp);
			}
			else if (tmp->type == INSTRUCTION)
				n_c_i[2] = True;
			tmp = tmp->next;
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

/*
** Check bot name and comment lengths
** ft_slen(...) - 2 because fields contain double-quotes
*/

void	check_lengths(t_asm *asms)
{
	if (ft_slen(asms->name) - 2 > PROG_NAME_LENGTH)
		ft_panic(1, "Champion name too long (Max length %d)\n",
				PROG_NAME_LENGTH);
	else if (ft_slen(asms->comment) - 2 > COMMENT_LENGTH)
		ft_panic(1, "Champion comment too long (Max length %d)\n",
				COMMENT_LENGTH);
	else if (asms->cum_size > CHAMP_MAX_SIZE)
		ft_panic(1, "Champion size is too big (Max size %d)\n", CHAMP_MAX_SIZE);
}

/*
** Validate the file content
** @param content list of lines read from file
*/

t_list	*validate(t_asm *asms, t_list *lines)
{
	t_list	*tokens;

	tokens = tokenize(lines);
	check_name_comment(asms, tokens);
	check_duplicates(tokens);
	check_instructions(tokens);
	label_deref(asms, tokens);
	check_lengths(asms);
	return (tokens);
}
