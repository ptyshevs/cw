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

void	create_map(t_bot *bot, int bot_num)
{
	t_map			*map;
	int				to_place;
	unsigned int	i;
	int				k;

	(void)bot;
	k = 0;
	map = ft_memalloc(sizeof(t_map));
	to_place = MEM_SIZE / bot_num;
	ft_printf("%d\n", bot_num);
	int m = 0;
	while (m < bot_num)
	{
		i = 0;
		ft_printf("k: %d\n", k);
		k = to_place * m++;
		while (i < bot->header->size)
			map->map[k++] = bot->code[i++];
		ft_printf("%s: %p->%p\n", bot->header->name, bot);
	}
	k = 0;
	while (k < MEM_SIZE)
	{
		ft_printf("%d|", map->map[k]);
		if (k && k % 64 == 0)
			ft_printf("\n");
		k++;
	}	
	ft_printf("\n");
}

/*
** Read bot with a provided <id> from <filename> to array of bots in <map>
*/

void	read_bot(t_map *map, char *filename, unsigned int id)
{
	int		fd;
	t_bot	*bot;

	if (map->num_players == MAX_PLAYERS)
		ft_panic(1, "Too many champions\n");
	fd = 0; // using fd as counter
	while ((unsigned int) fd < map->num_players)
	{
		if (map->bots[fd]->id == id)
			ft_panic(1, "Bot with such id already exists: %s\n",
					 map->bots[fd]->header->name);
		fd++;
	}
	bot = create_new_bot(filename, id);
	map->bots[map->num_players++] = bot;
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
