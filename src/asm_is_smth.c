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
** it starts from 'r', but is it a register? If it's not, then
 * it's an INSTRUCTION
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
