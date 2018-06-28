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

void	logging(t_log log, char *brief, char *full)
{
	if (log.level == v_brief && brief)
		ft_dprintf(log.to, "%s\n", brief);
	else if (log.level == v_elaborate && full)
		ft_dprintf(log.to, "%s\n", full);
	else
		ft_panic(1, "Unrecognized log.level level (%d) or arguments:"
		"\n%s\n%s\n%s\n", log.level, brief, full);
}

/*
** Log something to <fd>
*/

void	log_this(t_log log, char *message, ...)
{
	va_list	ap;

	if (log.level > 0)
	{
		va_start(ap, message);
		ft_vdprintf(log.to, message, ap);
	}
}
