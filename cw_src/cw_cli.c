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
#include "viz.h"

/*
** Parse verbosity CLI argument (-v <1|2|3>)
*/

static int		parse_verbosity(t_map *map, int ac, char **av, int i)
{
	int	t;

	t = v_essential;
	if (i + 1 >= ac)
		ft_panic(1, "No verbosity level specified\n");
	if (!ft_strisnum(av[i + 1], 10) || (t = ft_atoi(av[i + 1])) < 0 || t > 511)
		ft_panic(1, "Bad verbosity level\n", av[i + 1]);
	map->log->level = (t_vrb)t;
	return (1);
}

/*
** Parse id CLI argument (-n <id> <bot>)
**
** If -n is found on i-th index, try to find number at i+1 and bot at i+2
*/

static t_bool	parse_id(t_map *map, int ac, char **av, int i)
{
	if (i + 1 >= ac)
		ft_panic(1, "No id specified\n");
	else if (!ft_strisnum(av[i + 1], 10))
		ft_panic(1, "Id specified is not a number: %s\n", av[i + 1]);
	if (i + 2 >= ac)
		ft_panic(1, "Unexpected end of arguments after specifying id\n");
	read_bot(map, av[i + 2], ft_atoi(av[i + 1]), True);
	return (True);
}

/*
** Parse dump argument (-d|--dump or -s|--stream)
*/

int				parse_dump(t_map *map, char *n, t_bool stream)
{
	if (ft_slen(n) == 0 || !ft_strisnum(n, 10))
		ft_panic(1, "Bad number of cycles specified for dump\n");
	map->dump->dump = True;
	map->dump->once = (t_bool)!stream;
	map->dump->n = ft_atoi(n);
	map->viz_mode = False;
	return (1);
}

/*
** Compare options, return increment of i. if return value is -1, then read bot.
** Don't ask why. Because I want to.
*/

int				parse_options(t_map *map, int ac, char **av, int i)
{
	if (ft_strequ(av[i], "-h") || ft_strequ(av[i], "--help"))
		show_usage();
	else if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "--dump"))
		return (parse_dump(map, av[i + 1], False));
	else if (ft_strequ(av[i], "-s") || ft_strequ(av[i], "--stream"))
		return (parse_dump(map, av[i + 1], True));
	else if (ft_strequ(av[i], "-c") || ft_strequ(av[i], "--colorful"))
		map->colorful = True;
	else if (ft_strequ(av[i], "-n") && parse_id(map, ac, av, i))
		return (2);
	else if (ft_strequ(av[i], "-v") || ft_strequ(av[i], "--verbose"))
		return (parse_verbosity(map, ac, av, i));
	else if (ft_strequ(av[i], "-z") || ft_strequ(av[i], "--viz"))
		map->viz_mode = True;
	else if (ft_strequ(av[i], "-i") || ft_strequ(av[i], "--identical"))
		map->log->identical = True;
	else
		return (-1);
	return (0);
}

/*
** Parse Command-line arguments
*/

void			parse_cli(t_map *map, int ac, char **av)
{
	int		i;
	int		cur_id;
	int		ret;

	if (ac == (cur_id = 1))
		show_usage();
	i = 0;
	while (++i < ac)
	{
		ret = parse_options(map, ac, av, i);
		if (ret == -1)
			read_bot(map, av[i], -cur_id++, False);
		else
			i += ret;
	}
	if (map->n_bots == 0)
		show_usage();
}
