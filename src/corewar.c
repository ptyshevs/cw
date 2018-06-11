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

#include "ft_printf.h"
#include "gnls.h"
#include "cw.h"
#include <fcntl.h>

int		usage()
{
	write(1, "Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n"
		"-a        : Prints output from 'aff' (Default is to hide it)\n"
"#### TEXT OUTPUT MODE ##########################################################\n"
    "-d N      : Dumps memory after N cycles then exits\n"
    "-s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
    "-v N      : Verbosity levels, can be added together to enable several\n"
    "- 0	   : Show only essentials\n"
    "- 1	   : Show lives\n"
    "- 2	   : Show cycles\n"
    "- 4	   : Show operations (Params are NOT litteral ...)\n"
    "- 8	   : Show deaths\n"
    "- 16	   : Show PC movements (Except for jumps)\n"
"#### BINARY OUTPUT MODE ########################################################\n"
    "-b        : Binary output mode for corewar.42.fr\n"
    "--stealth : Hides the real contents of the memory\n"
"#### NCURSES OUTPUT MODE #######################################################\n"
    "-n        : Ncurses output mode\n"
    "--stealth : Hides the real contents of the memory\n"
"################################################################################\n", 1161);
	return (0);
}

t_bot	*init_bot(t_bot *bot)
{
	bot->name = NULL;
	bot->comment = NULL;
	bot->size = 0;
	bot->id = 0;
	return (bot);
}

void	read_file(t_bot *bot, char *file_name)
{
	char	*str;

	str = NULL;
	int fd = open(file_name, O_RDONLY);
	size_t filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char *content = ft_memalloc(filesize);
	ft_printf("read returned %d\n", read(fd, content, filesize));
	write(1, content, filesize);
	ft_printf("file content: %s\n", content);
	ft_printf("gnl returned: %d\n", ft_gnl(fd, &str));
	ft_printf("%s\n", str);
	(void)bot;
}

int		main(int ac, char **av)
{
	t_bot bot;
	if (ac == 1)
		return (usage());
	init_bot(&bot);
	if (open(av[1], O_RDONLY) == -1)
	{
		write(1, "Can't read source file\n", 23);
		return (1);
	}
	read_file(&bot, av[1]);
	return (0);
}