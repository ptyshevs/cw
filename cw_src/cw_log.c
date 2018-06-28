/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:42:51 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 20:43:05 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Log message either to stdout (default behavior) or to fd
*/

void	logging(char *brief, char *standard, char *elaborate)
{
	static	t_vrb	verbosity = v_none;
	static	int		fd = 1;

	if ((unsigned long)brief == 42U && verbosity == v_none)
	{
		verbosity = (t_vrb)standard;
		fd = (int)elaborate;
		return ;
	}
	if (verbosity == v_brief && brief)
		ft_dprintf(fd, "%s\n", brief);
	else if (verbosity == v_standard && standard)
		ft_dprintf(fd, "%s\n", standard);
	else if (verbosity == v_elaborate && elaborate)
		ft_dprintf(fd, "%s\n", elaborate);
	else
		ft_panic(1, "Unrecognized verbosity level (%d) or arguments:"
		"\n%s\n%s\n%s\n", verbosity, brief, standard, elaborate);
}

/*
** Log something to <fd>
*/

void	log_this(int fd, char *message, ...)
{
	va_list	ap;

	va_start(ap, message);
	ft_vdprintf(fd, message, ap);
}
