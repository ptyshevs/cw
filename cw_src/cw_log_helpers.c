/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_log_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:06:14 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 00:06:27 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Add players introduction to log
*/

void	introduce_bots(t_map *map)
{
	t_uint		i;
	t_bot		*bot;

	i = 0;
	while (i < map->n_bots)
	{
		if (i == 0)
			to_log(map, "Introducing contestants...\n");
		bot = map->bots[i];
		if (map->log->identical)
			to_log(map, "* Player %d, weighing %d bytes, \"%s\" (\"%s\")!\n",
			i + 1, bot->header->size, bot->header->name,
			bot->header->comment);
		else
			to_log(map, "* Player %d, weighting %d bytes, \"%s\" (\"%s\")!\n",
			i + 1, bot->header->size, bot->header->name,
			bot->header->comment);
		i++;
	}
}

/*
** Log more info on sti instruction, if necessary.
*/

void	log_sti(t_map *map, t_uint first_arg, t_uint sec_arg)
{
	if (!(map->log->level & v_ops))
		return ;
	to_log(map, "       | -> store to %d + %d = %d (with pc and mod 14)\n",
		first_arg, sec_arg, first_arg + sec_arg);
}
