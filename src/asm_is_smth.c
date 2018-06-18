/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_is_smth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:07:46 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/13 17:09:22 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** it starts from 'r', but is it a register?
** If it's not, then it's an INSTRUCTION
*/

t_bool	is_register(char *line, int start)
{
	int		cnt_digits;

	cnt_digits = 0;
	while (line[++start])
	{
		if (ft_isdigit(line[start]))
			cnt_digits++;
		else
			break ;
	}
	if (cnt_digits == 0 || cnt_digits > 2)
		return (FALSE);
	return (TRUE);
}

/*
** It consists of LABEL_CHARS and ends with LABEL_CHAR?
*/

t_bool	is_label(char *line, int start, int line_nbr)
{
	int		i;

	if (line[start] == LABEL_CHAR)
		return (FALSE); // Indirect label (starts with `:`)
	i = start;
	while (line[i])
	{
		if (line[i] == LABEL_CHAR)
			return (TRUE);
		else if (ft_isspace(line[i]) || line[i] == DIRECT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, line[i]))
		{
//			ft_dprintf(2, "[d] is_label has found char not from a LABEL_CHARS: %c\n", line[i]);
			lexical_error(line_nbr, i + 1);
		}
		i++;
	}
	return (FALSE);
}

/*
** Check if token is an indirect value - starts from a number (or minus)
*/

t_bool	is_indirect(char *line, int start)
{
	int		i;

	i = start;
	if (line[i] == '-') // negative number is ok
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			break ;
		else
			i++;
	}
	if (line[start] == '-' ? i - start < 2 : i - start == 0)
		return (FALSE);
	return (TRUE);
}

/*
** Check if the token type provided is a valid parameter type
*/

t_bool	is_parameter(t_type type)
{
	return (t_bool)(type == INDIRECT || type == INDIRECT_LABEL ||
				type == DIRECT || type == DIRECT_LABEL ||
				type == REGISTER);
}
