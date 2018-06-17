/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:04:05 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/17 19:04:07 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

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

t_bot			*creat_new_bot(t_bot *bot)
{
	while (bot->next)
		bot = bot->next;
	bot->next = ft_memalloc(sizeof(t_bot));
	bot->next->header = ft_memalloc(sizeof(header_t));
	return (bot->next);
}
