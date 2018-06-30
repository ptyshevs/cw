/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_cli.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 07:40:13 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 07:40:28 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Parse verbosity CLI argument (-v <1|2|3>)
*/

static void	parse_verbosity(t_map *map, int ac, char **av, int i)
{
	int	tmp;

	if (i + 1 >= ac)
		ft_panic(1, "No verbosity specified. Use 1, 2, or 3.\n");
	if ((tmp = ft_atoi(av[i + 1])) < 1 || tmp > 3)
		ft_panic(1, "Bad verbosity level. Use 1, 2, or 3. ", av[i + 1]);
	map->log.level = (t_vrb)tmp;
}

/*
** Parse id CLI argument (-n <id>)
*/

static void	parse_id(t_map *map, int ac, char **av, int i)
{
	if (i + 1 >= ac)
		ft_panic(1, "No id specified\n");
	else if (!ft_strisnum(av[i + 1], 10))
		ft_panic(1, "Id specified is not a number: %s\n", av[i + 1]);
	if (i + 2 >= ac)
		ft_panic(1, "Unexpected end of arguments after specifying id\n");
	read_bot(map, av[i + 2], ft_atoi(av[i + 1]), True);
}



/*
** Parse Command-line arguments
*/

void		parse_cli(t_map *map, int ac, char **av)
{
	int		i;
	int		cur_id;

	if (ac == (cur_id = 1))
		show_usage();
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-h") || ft_strequ(av[i], "--help"))
			show_usage();
		else if (ft_strequ(av[i], "-n"))
		{
			parse_id(map, ac, av, i);
			i += 2;
		}
		else if (ft_strequ(av[i], "-v"))
			parse_verbosity(map, ac, av, i++);
		else if (ft_strequ(av[i], "-z"))
			map->viz.on = True;
		else
			read_bot(map, av[i], -cur_id++, False);
	}
}

/*
** Set default pref for map
*/

void	set_default_pref(t_map *map)
{

	map->log.level = v_none;
	map->log.to = 1;
	map->pref.cycles_to_die = CYCLE_TO_DIE;
	map->pref.cycle_delta = CYCLE_DELTA;
	map->pref.max_checks = MAX_CHECKS;
	map->pref.nbr_live = NBR_LIVE;
}
