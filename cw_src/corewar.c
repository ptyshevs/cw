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
		ft_printf("%s: %p->%p\n", bot->header->prog_name, bot, bot->next);
		bot = bot->next;
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

int		main(int ac, char **av)
{
	t_bot			*bot;
	unsigned int	i;
	t_bot			*check;

	bot = init_bot();
	i = 1;
	if (ac == 1)
		show_usage();
	check = bot;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-n") == 0)
			ft_panic("Flag detected!\n", 2, 1);
		if (open(av[i], O_RDONLY) == -1)
			ft_panic("Can't read source file\n", 2, 1);
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
