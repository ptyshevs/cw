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

/*
** Read executable code
*/

unsigned char	*read_code(char *filename, int fd)
{
	(void)filename;
	(void)fd;
	return (NULL);
}


/*
** Read 4 bytes of magic, validate the cumulative number
*/

unsigned int	parse_magic(char *filename, int fd)
{
	t_line			*magic;
	unsigned int	nbr;
	int				i;

	magic = read_n_bytes(fd, 4);
	nbr = 0;
	i = 0;
	while (i < 4)
		nbr = (nbr << 8) + magic->str[i++];
	if (nbr != COREWAR_EXEC_MAGIC)
		invalid_header(filename);
	clean_t_line(&magic);
	return (nbr);
}

/*
** Parse bot name, which length is defined by PROG_NAME_LENGTH
*/

char	*parse_name(char *filename, int fd)
{
	(void)filename;
	(void)fd;
	return (NULL);
}


/*
** Read and validate header
*/

t_header	*read_header(char *filename, int fd)
{
	t_header		*header;

	header = ft_memalloc(sizeof(t_header));
	header->magic = parse_magic(filename, fd);
	ft_strcpy(header->name, parse_name(filename, fd));
//	header->size = check_size(find_size(file));
//	ft_strcpy(header->comment, check_comment(find_comment(file)));
	return (header);
}

char			*find_comment(const unsigned char *file)
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

char			*check_comment(const char *comment)
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

/*
** Create new bot alongside with validating successfully opened file
*/

t_bot			*create_new_bot(char *filename, unsigned int id)
{
	t_bot	*bot;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1) // now fd is file descriptor
		ft_panic(1, "Can't read source file %s\n", filename);
	bot = ft_memalloc(sizeof(t_bot));
	bot->id = id;
	bot->header = read_header(filename, fd);
	bot->code = read_code(filename, fd);
	return (bot);
}
