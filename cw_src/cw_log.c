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
** Log to vizualization
*/

void	to_vlog(t_map *map, char *message, va_list ap)
{
	int		i;

	if (map->log->log[map->log->length - 1])
		ft_strdel(&map->log->log[map->log->length - 1]);
	i = map->log->cur_length - 1;
	while (i >= 0)
	{
		map->log->log[i + 1] = map->log->log[i];
		i--;
	}
	map->log->log[0] = ft_vsprintf(message, ap);
	map->log->cur_length += map->log->cur_length < map->log->length ? 1 : 0;
}

/*
** Log smth, either to log->fd, or to viz log
*/

void	to_log(t_map *map, char *message, ...)
{
	va_list	ap;

	va_start(ap, message);
	if (!map->viz_mode)
		ft_vdprintf(map->log->to, message, ap);
	else
		to_vlog(map, message, ap);
}

/*
** Log something that has happened on the map, adding message to it
*/

void	log_map(t_map *map, t_proc *pr, char *message, ...)
{
	va_list	ap;
	char	*tmp;

	if (map->log->level > v_essential)
	{
		va_start(ap, message);
		tmp = ft_vsprintf(message, ap);
		to_log(map, "%#06x %02x %s: %s\n", pr->pc + 1, get_map(map, pr->pc),
			pr->cur_ins->name, tmp);
	}
}
