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
			to_log(map, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
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
** Log live command if verbosity has alive flag in level
*/

void	log_live(t_map *map, t_uint index)
{
	if (map->log->level & v_alive)
		to_log(map, "Player %d (%s) is said to be alive\n", index + 1,
			map->bots[index]->header->name);
}

/*
** Log more info on sti instruction, if necessary.
*/

void	log_sti(t_map *map, t_proc *pr, t_uint first_arg, t_uint sec_arg)
{
	if (!(map->log->level & v_ops))
		return ;
	to_log(map, "P%5d | %s r%hd %hd %hd\n", pr->index, pr->cur_ins->name,
		pr->args[0].value, first_arg, sec_arg);
	to_log(map, "       | -> store to %hd + %hd = %hd (with pc and mod %hd)\n",
		first_arg, sec_arg, first_arg + sec_arg, pr->pc + first_arg + sec_arg);
}

void	log_ldi(t_map *map, t_uint pc, t_uint first_arg, t_uint sec_arg)
{
	if (!(map->log->level & v_ops))
		return ;
	to_log(map, "       | -> load from %hd + %hd = %hd (with pc and mod %hd)\n",
		first_arg, sec_arg, first_arg + sec_arg, pc + first_arg + sec_arg);
}

void	log_reg(t_map *map, t_proc *pr)
{
	if (!(map->log->level & v_reg))
		return ;
	to_log(map, "P%5d reg | [%d %d %d %d][%d %d %d %d]"
				"[%d %d %d %d][%d %d %d %d]\n", pr->index,
		pr->reg[0], pr->reg[1], pr->reg[2], pr->reg[3], pr->reg[4], pr->reg[5],
	pr->reg[6], pr->reg[7], pr->reg[8], pr->reg[9], pr->reg[10], pr->reg[11],
	pr->reg[12], pr->reg[13], pr->reg[14], pr->reg[15]);
}
