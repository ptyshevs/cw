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
** Log smth, either to log->fd, or to viz log
*/

void	to_valog(t_map *map, char *message, va_list ap)
{
	map->viz_mode ? to_vlog(map, message, ap) :
					ft_vdprintf(map->log->to, message, ap);
}

/*
** Log something that has happened on the map, adding message to it
*/

void	log_map(t_map *map, t_proc *pr, char *message, ...)
{
	va_list	ap;
	char	*tmp;

	if (map->log->level & v_more)
	{
		va_start(ap, message);
		tmp = ft_vsprintf(message, ap);
		to_log(map, "%#06x %s: %s\n", pr->pc + 1, pr->cur_ins->name, tmp);
	}
}

/*
** Log live command if verbosity has alive flag in level
*/

void	log_live(t_map *map, t_uint index)
{
	if (map->log->level & v_alive)
		to_log(map, "Player %d (%s) is said to be alive\n", index + 1,
			map->bots[index]->header->name);
}

/*
** Log only if more flag is specified
*/

void	log_more(t_map *map, char *message, ...)
{
	va_list	ap;

	if (map->log->level & v_more)
	{
		va_start(ap, message);
		to_valog(map, message, ap);
	}
}
