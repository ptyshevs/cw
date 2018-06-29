/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 13:25:34 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 13:25:56 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Find t_op instruction by its <op>
*/

const t_op	*find_instr(t_uint op)
{
	if (op == 0 || op > 16)
		return (NULL);
	else
		return (&g_op_tab[op - 1]);
}

/*
** Expand codage into an array of types of argument to expect. It takes max. 3
** bytes, since this is max number of arguments allowed.
*/

t_uc	*expand_codage(t_uint codage)
{
	t_uc	*args;
	int		i;

	args = ft_memalloc(3);
	i = 0;
	while (i < 3)
	{
		args[i] = (t_uc)((codage >> (6 - i * 2)) & 0x3);
		i++;
	}
	return (args);
}

/*
** Execute command on which the process currently positioned
*/

void	exec(t_map *map, t_proc *pr)
{
	const t_op *instr = find_instr(map->map[pr->pc]);
	if (instr->codage)
	{
		t_uc *args = expand_codage(map->map[pr->pc + 1]);
		show_args(args);
	}
	ft_printf("%02X\n", map->map[pr->pc]);
}

/*
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;

	map.log.level = v_none;
	map.log.to = 1;
	parse_cli(&map, ac, av);
	inhabit_map(&map);
	init_procs(&map);
	if (map.log.level > v_none)
	{
//		show_bots(map.bots, map.n_bots);
//		show_map(&map);
	}
	show_procs(map.procs);
	exec(&map, map.procs);
	return (0);
}
