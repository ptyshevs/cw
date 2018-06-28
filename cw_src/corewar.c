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
** Inhabit map with bots
*/

void	inhabit_map(t_map *map)
{
	int				to_place;
	unsigned int	i;
	int				k;
	int				m;

	to_place = MEM_SIZE / map->num_players;
	m = 0;
	while (m < map->num_players)
	{
		i = 0;
		k = to_place * m;
		map->bots[m]->start_pos = k;
		while (i < map->bots[m]->header->size)
			map->map[k++] = map->bots[m]->code[i++];
		m++;
	}
}

/*
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;
//	t_bot			*bot;
//	unsigned int	i;
//	t_bot			*check;

	parse_cli(&map, ac, av);
	logging((char *)42, map.v ? (char *)(t_vrb)map.v : (char *)v_standard, (char *)1);
	show_bots(map.bots, map.num_players);
	inhabit_map(&map);
	show_map(&map);
//	bot = init_bot();
//	i = 1;
//	check = bot;
//	while (av[i])
//	{
//		if (ft_strcmp(av[i], "-n") == 0)
//			ft_panic(1, "Flag detected!\n");
//		if (open(av[i], O_RDONLY) == -1)
//			ft_panic(1, "Can't read source file\n");
//		else
//		{
//			bot->id = i;
//			complete_file(av[i], bot);
//			av[i + 1] ? bot = creat_new_bot(bot) : 0;
//		}
//		i++;
//	}
//	create_map(check, i - 1);
	return (0);
}
