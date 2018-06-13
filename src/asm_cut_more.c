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

t_tk	*cut_separator(char *line, int start, int line_nbr)
{

}
