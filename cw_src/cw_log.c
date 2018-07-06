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
		to_log(map, pr->pc == 0 ? "0x000%d %s: %s\n" : "%#06x %s: %s\n",
			pr->pc, pr->cur_ins->name, tmp);
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

void	log_zjmp(t_map *map, t_proc *pr)
{
	if (pr->carry)
		to_log(map, "P%5d | zjmp %hd OK\n", pr->index, get_arg(map, pr, 0, False));
	else
		to_log(map, "P%5d | zjmp %hd FAILED\n", pr->index, get_arg(map, pr, 0, False));
}

void	log_fork(t_map *map, t_proc *pr, t_uint new_pc)
{
	if (map->log->level & v_ops)
		to_log(map, "P%5d | %s %d (%u)\n", pr->index, pr->cur_ins->name,
			pr->args[0].value, new_pc);
}

void	log_args(t_map *map, t_proc *pr)
{
	if (!(map->log->level & v_args))
		return ;
	if (pr->cur_ins->nargs == 1)
		to_log(map, "P%5d | %s\n", pr->index, arg_to_str(pr->args[0].type));
	else if (pr->cur_ins->nargs == 2)
		to_log(map, "P%5d | %s %s\n", pr->index, arg_to_str(pr->args[0].type),
			arg_to_str(pr->args[1].type));
	else
		to_log(map, "P%5d | %s %s %s\n", pr->index, arg_to_str(pr->args[0].type),
			arg_to_str(pr->args[1].type), arg_to_str(pr->args[2].type));
}

/*
** Log instruction and its artuments
*/

void	log_instruction(t_map *map, t_proc *pr)
{
	char	*tmp;
	t_uint	i;

	if (!(map->log->level & v_ops))
		return ;
	if (pr->cur_ins->op == 9)
		return log_zjmp(map, pr);
	else if (pr->cur_ins->op == 12 || pr->cur_ins->op == 15 || pr->cur_ins->op == 11)
		return ;
	tmp = ft_sprintf("P%5d | %s", pr->index, pr->cur_ins->name);
	i = 0;
	while (i < pr->cur_ins->nargs)
	{
		tmp = ft_concat(tmp, ft_sprintf(
				(pr->args[i].type == T_REG ? " r%d" : " %d"),
				pr->args[i].value), True);
		i++;
	}
	to_log(map, "%s\n", tmp);
	ft_strdel(&tmp);
}

/*
** Log movement that follows after executing valid instruction
*/

void	log_move(t_map *map, t_proc *pr, t_uint n)
{
	char	*cmb;
	char	*t;
	t_uint	i;

	cmb = NULL;
	i = 0;
	while (i < n)
	{
		t = ft_sprintf(i + 1 < n || map->log->identical ? "%02x " : "%02x", get_map(map, pr->pc + i));
		cmb = ft_concat(cmb, t, True);
		i++;
	}
	if (pr->pc == 0)
		to_log(map, "ADV %u (0x0000 -> %#06x) %s\n", n, pr->pc + n, cmb);
	else if (pr->pc + n == 0)
		to_log(map, "ADV %u (%#06x -> 0x0000) %s\n", n, pr->pc, cmb);
	else
		to_log(map, "ADV %u (%#06x -> %#06x) %s\n", n, pr->pc, pr->pc + n, cmb);
	ft_strdel(&cmb);
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
