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
	else if (log.level == v_full && full)
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

	if (log.level > v_none)
	{
		va_start(ap, message);
		ft_vdprintf(log.to, message, ap);
	}
}

/*
** Log something that has happened on the map, adding message to it
*/

void	log_map(t_map *map, t_proc *pr, char *message, ...)
{
	va_list	ap;

	if (map->log.level > v_none)
	{
		va_start(ap, message);
		ft_dprintf(map->log.to, "%u %02x %s: ", pr->pc + 1,
					get_map(map, pr->pc), pr->cur_ins->name);
		ft_vdprintf(map->log.to, message, ap);
		ft_dprintf(map->log.to, "\n");
	}
}
