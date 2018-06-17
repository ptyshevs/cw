/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cut_indirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 21:57:07 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/17 21:58:41 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Cut indirect label in format `:blablabla`
*/

t_tk	*cut_indirect_label(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = *start + 1;
	while (line[i])
	{
		if (ft_isspace(line[i]) ||
				line[i] == SEPARATOR_CHAR || line[i] == DIRECT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, line[i]))
			lexical_error(line_nbr, i + 1);
		i++;
	}
	tk = ft_strtrunc(&(line[*start]), i - *start, FALSE);
	token = create_token(tk, line_nbr, i, INDIRECT_LABEL);
	*start = i - 1;
	return (token);
}

/*
** Cut indirect - number that doesn't start with `%`.
** e.g. 151, -42, -0, etc.
*/

t_tk	*cut_indirect(char *line, int *start, int line_nbr)
{
	t_tk	*token;
	char	*tk;
	int		i;

	i = line[*start] == '-' ? *start + 1 : *start;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			break ;
		i++;
	}
	tk = ft_strtrunc(&(line[*start]), i - *start, FALSE);
	token = create_token(tk, line_nbr, i, INDIRECT);
	*start = i - 1;
	return (token);
}
