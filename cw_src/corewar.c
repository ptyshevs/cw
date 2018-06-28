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
	t_map	*map;
	int		to_place;
	unsigned int		i;
	int		k;

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
		while (i < bot->header->prog_size)
			map->map[k++] = bot->code[i++];
		ft_printf("%s: %p->%p\n", bot->header->prog_name, bot);
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

}

/*
** Parse Command-line arguments
*/

void	parse_cli(t_map *map, int ac, char **av)
{
	int				i;
	unsigned int	cur_id;

	if (ac == (cur_id = 1))
		show_usage();
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-h") || ft_strequ(av[i], "--help"))
			show_usage();
		else if (ft_strequ(av[i], "-n"))
		{
			if (i + 1 >= ac || !ft_strisnum(av[i + 1], 10))
				ft_panic(1, "Bad %d-th argument (after -n flag): %s\n", av[i + 1]);
			read_bot(map, av[i + 2], (unsigned int)ft_atoi(av[i + 2]));
		}
		else if (ft_strequ(av[i], "-v"))
		{
			if ((map->verbosity = ft_atoi(av[i + 1])) < 1 || map->verbosity > 3)
				ft_panic(1, "Bad verbosity level. Use 1, 2, or 3. "
							"Greater means more: %s\n", av[i + 1]);
		}
		else
			read_bot(map, av[i], cur_id++);
	}
}

/*
** Virtual Arena
*/

int		main(int ac, char **av)
{
	static t_map	map;
	t_bot			*bot;
	unsigned int	i;
	t_bot			*check;

	parse_cli(&map, ac, av);
	logging((char *) 42, (char *)(map.verbosity ?
			(t_verbosity)map.verbosity : v_standard), (char *)1);
	bot = init_bot();
	i = 1;
	if (ac == 1)
		show_usage();
	check = bot;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-n") == 0)
			ft_panic(1, "Flag detected!\n");
		if (open(av[i], O_RDONLY) == -1)
			ft_panic(1, "Can't read source file\n");
		else
		{
			bot->id = i;
			complete_file(av[i], bot);
			av[i + 1] ? bot = creat_new_bot(bot) : 0;
		}
		i++;
	}
	create_map(check, i - 1);
	return (0);
}
