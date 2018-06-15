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
#include "ft_gnls.h"
#include "ft_str.h"
#include "ft_strnum.h"
#include "cw.h"
#include "ft_tell.h"
#include <fcntl.h>

int				usage(void)
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

t_bot			*init_bot(void)
{
	t_bot			*bot;

	bot = ft_memalloc(sizeof(t_bot));
	bot->header = ft_memalloc(sizeof(header_t));
	return (bot);
}

unsigned int	check_magic(unsigned char *magic)
{
	unsigned int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (i < 4)
		nbr = (nbr << 8) + magic[i++];
	// ft_printf("magic is %0X\n", nbr);

	if (nbr != COREWAR_EXEC_MAGIC)
		ft_panic("Magic is bad", 2, 1);
	return (nbr);
}

unsigned char	*find_magic(unsigned char *file)
{
	unsigned char	*first_four;
	int				i;
	int				j;

	first_four = ft_memalloc(sizeof(char) * 4);
	i = 0;
	j = 0;
	while (i < 4)
		first_four[j++] = file[i++];
	// ft_printf("%d|%d|%d|%d\n", first_four[0], first_four[1], first_four[2], first_four[3]);
	return (first_four);
}

unsigned char	*read_file(char *file_name)
{
	unsigned char	*content;
	int				fd;
	size_t			filesize;

	fd = open(file_name, O_RDONLY);
	filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	content = ft_memalloc(filesize);
	ft_printf("read returned %d\n", read(fd, content, filesize));
	return (content);
}

unsigned char	*find_size(unsigned char *file)
{
	unsigned char	*size;
	int				i;
	int				j;

	size = ft_memalloc(sizeof(char) * 4);
	i = PROG_NAME_LENGTH + 8;
	j = 0;
	while (i < PROG_NAME_LENGTH + 12)
		size[j++] = file[i++];
	// ft_printf("%d|%d|%d|%d\n", size[0], size[1], size[2], size[3]);
	// ft_printf("%d\n", i);
	return (size);
}

unsigned char	*find_code(unsigned char *file)
{
	unsigned char	*code;
	unsigned int	i;
	unsigned int	j;

	code = ft_memalloc(sizeof(char) * 3185);
	i = 2191;
	j = 0;
	while (i < 3185)
		code[j++] = file[i++];
	j = 0;
	while (j < 1020)
		ft_printf("%d|", code[j++]);
	ft_printf("\n");
	return (code);
}

unsigned int	check_size(unsigned char *size)
{
	unsigned int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (i < 4)
		nbr = (nbr << 8) + size[i++];
	ft_printf("size is %0X\n", nbr);
	return (nbr);
}

char			*find_name(unsigned char *file)
{
	char			*name;
	int				i;
	int				j;

	name = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	i = 4;
	j = 0;
	while (i < PROG_NAME_LENGTH + 1)
		name[j++] = file[i++];
	j = 0;
	// while (j < PROG_NAME_LENGTH + 1)
	// 	ft_printf("%d|", name[j++]);
	// ft_printf("\n");
	return (name);
}

char			*check_name(char *name)
{
	unsigned int	nbr;
	char			*ret;
	int				i;
	int				j;

	nbr = 0;
	i = 0;
	j = 0;
	ret = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	while (name[i] != 0)
	{
		nbr = 0;
		nbr = (nbr << 8) + name[i++];
		ret[j++] = nbr;
	}
	return (ret);
}

char			*find_comment(unsigned char *file)
{
	char			*comment;
	int				i;
	int				j;

	comment = ft_memalloc(sizeof(char) * (COMMENT_LENGTH + 1));
	i = 140;
	j = 0;
	while (i < 140 + COMMENT_LENGTH + 1)
		comment[j++] = file[i++];
	j = 0;
	return (comment);
}

char			*check_comment(char *comment)
{
	unsigned int	nbr;
	char			*ret;
	int				i;
	int				j;

	nbr = 0;
	i = 0;
	j = 0;
	ret = ft_memalloc(sizeof(char) * (COMMENT_LENGTH + 1));
	while (comment[i] != 0)
	{
		nbr = 0;
		nbr = (nbr << 8) + comment[i++];
		ret[j++] = nbr;
	}
	return (ret);
}

void			complete_file(char *file_name, t_bot *bot)
{
	unsigned char	*file;

	file = read_file(file_name);
	bot->header->magic = check_magic(find_magic(file));
	ft_printf("magic is %0X\n", bot->header->magic);
	bot->name = check_name(find_name(file));
	ft_printf("name is %s\n", bot->name);
	bot->size = check_size(find_size(file));
	ft_printf("size is %d\n", bot->size);
	bot->comment = check_comment(find_comment(file));
	ft_printf("comment is %s\n", bot->comment);
	bot->code = find_code(file);
}

t_bot 	*creat_new_bot(t_bot *bot)
{
	while (bot->next)
		bot = bot->next;
	bot->next = ft_memalloc(sizeof(t_bot));
	bot->next->header = ft_memalloc(sizeof(header_t));
	return (bot->next); 
}

int				main(int ac, char **av)
{
	t_bot			*bot;
	int				i;
	t_bot 			*check;

	bot = init_bot();
	i = 1;
	if (ac == 1)
		return (usage());
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
			if (av[i + 1])
				bot = creat_new_bot(bot);
		}
		i++;
	}
	i = 0;
	while (check)
	{
		ft_printf("%p:, %d: %s\n", check, i++, check->name);
		check = check->next;
	}
	return (0);
}
