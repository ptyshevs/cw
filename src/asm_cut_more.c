/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cut_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:19:57 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/13 17:20:09 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Cut register in format rX[X], where X - digit, [X] another optional digit
*/

t_tk	*cut_register(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = *start + 1;
	i += ft_isdigit(line[i]) ? 1 : 0;
	i += ft_isdigit(line[i]) ? 1 : 0;
	tk = ft_strtrunc(&(line[*start]), i - *start, FALSE);
	token = create_token(tk, line_nbr, *start, REGISTER);
	*start = i - 1;
	return (token);
}

/*
** Cut separator (,). Hope it will be useful when validating instructions
*/

t_tk	*cut_separator(char *line, const int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;

	tk = ft_strtrunc(&(line[*start]), 1, FALSE);
	token = create_token(tk, line_nbr, *start, SEPARATOR);
	return (token);
}

/*
** Cut label in format `blablabla:`
*/

t_tk	*cut_label(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = ft_strchr(&(line[*start]), LABEL_CHAR) - &(line[*start]);
	tk = ft_strtrunc(&(line[*start]), i + 1, FALSE);
	token = create_token(tk, line_nbr, *start + 1, LABEL);
	*start += i;
	return (token);
}

/*
** Cut an instruction, hopefully
*/

t_tk	*cut_instruction(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = *start;
	while (line[i])
	{
		if (ft_isspace(line[i]) || ft_strchr("%,:", line[i]))
			break ;
		if (!ft_strchr(LABEL_CHARS, line[i]))
		{
//			ft_dprintf(2, "[d] cut_instruction(%s)\n", &(line[*start]));
			lexical_error(line_nbr, i + 1);
		}
		i++;
	}
	tk = ft_strtrunc(&(line[*start]), i - *start, FALSE);
	token = create_token(tk, line_nbr, *start + 1, INSTRUCTION);
	*start = i - 1;
	return (token);
}

/*
** Cut everything that starts with a dot.
** JK ;) cut only .name or .comment, everything else is a lexical error
*/

t_tk	*cut_spec(char *line, int *start, int line_nbr)
{
	t_tk	*token;

	token = NULL;
	if (ft_strnequ(&(line[*start]), NAME_CMD_STRING, ft_slen(NAME_CMD_STRING)))
	{
		token = create_token(ft_strdup(NAME_CMD_STRING), line_nbr,
							*start, COMMAND);
		*start += ft_slen(NAME_CMD_STRING) - 1;
	}
	else if (ft_strnequ(&(line[*start]), COMMENT_CMD_STRING,
						ft_slen(COMMENT_CMD_STRING)))
	{
		token = create_token(ft_strdup(COMMENT_CMD_STRING), line_nbr,
							*start, COMMAND);
		*start += ft_slen(COMMENT_CMD_STRING) - 1;
	}
	else
		lexical_error(line_nbr, *start + 1);
	return (token);
}
