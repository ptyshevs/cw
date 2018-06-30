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
** Delete last <n> entries from the list
*/

void	ft_lstdel_last(t_list **ahead, int len, int n)
{
	int		i;
	t_list	*tmp;
	t_list	*prev;

	tmp = *ahead;
	i = 1;
	while (i < len - n)
	{
		tmp = tmp->next;
		i++;
	}
	while (n > 1)
	{
		prev = tmp;
		tmp = tmp->next;
		n--;
		ft_memdel(&prev->content);
		ft_memdel((void **)&prev);
	}
}

/*
** Log to vizualization
*/

void	to_vlog(t_map *map, char *message, va_list ap)
{
	char	*str;

	str = ft_vsprintf(message, ap);
	ft_lstadd(&map->log.log, ft_lstnew(str, ft_slen(str) + 1));
	map->log.cur_length++;
	if (map->log.cur_length > map->log.length)
	{
		ft_lstdel_last(&map->log.log, map->log.cur_length,
					map->log.cur_length - map->log.length);
		map->log.cur_length = map->log.length;
	}
}

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
** Log smth, either to log.fd, or to viz log
*/

void	to_log(t_map *map, char *message, ...)
{
	va_list	ap;

	va_start(ap, message);
	if (!map->viz_mode)
		ft_vdprintf(map->log.to, message, ap);
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

	if (map->log.level > v_essential)
	{
		va_start(ap, message);
		tmp = ft_vsprintf(message, ap);
		to_log(map, "%u %02x %s: %s\n", pr->pc + 1, get_map(map, pr->pc),
			pr->cur_ins->name, tmp);
//		ft_vdprintf(map->log.to, message, ap);
//		ft_dprintf(map->log.to, "\n");
	}
}

/*
** Log bot (essential information)
*/

void	log_bot(t_map *map, t_bot *bot)
{
	to_log(map, "WHATEVER BOT IS COMING");
	if (map->n_bots == 1)
		to_log(map, "Introducing contestants...\n");
	to_log(map, "* Player %d, weighting %d bytes, \"%s\" (\"%s\")!\n",
	map->n_bots, bot->header->size, bot->header->name, bot->header->comment);
}
