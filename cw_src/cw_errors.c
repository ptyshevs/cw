/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:19:06 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 15:30:46 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** This error is raised when either of the following events happened:
** - magic is incorrect
** TODO: Add other cases when this is invoked
*/

void	invalid_header(char *filename)
{
	ft_panic(1, "Error: File %s has an invalid header\n", filename);
}
