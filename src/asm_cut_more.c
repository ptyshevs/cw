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

}
