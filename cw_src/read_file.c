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
** Collect first <n> bytes from <bytes> into a single number
*/

unsigned int	bytes_to_uint(t_uc *bytes, int n)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while (i < n)
		nbr = (nbr << 8) + bytes[i++];
	return (nbr);
}


/*
** Read 4 bytes of magic, validate the cumulative number
*/

unsigned int	parse_magic(char *filename, int fd)
{
	t_line			*magic;
	unsigned int	nbr;

	magic = read_n_bytes(filename, fd, 4);
	nbr = bytes_to_uint(magic->str, (int)magic->len);
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
	t_line	*name;
	t_uc	*ret;

	name = read_n_bytes(filename, fd, PROG_NAME_LENGTH);
	ret = name->str;
	ft_memdel((void **)&name);
	return ((char *)ret);
}

/*
** Parse bot comment, which length is defined by COMMENT_LENGTH
*/

char	*parse_comment(char *filename, int fd)
{
	t_line	*comment;
	t_uc	*ret;

	comment = read_n_bytes(filename, fd, PROG_NAME_LENGTH);
	ret = comment->str;
	ft_memdel((void **)&comment);
	return ((char *)ret);
}

/*
** Parse bot size, which takes 4 bytes
*/

unsigned int	parse_size(char *filename, int fd)
{
	t_line			*size;
	unsigned int	nbr;

	size = read_n_bytes(filename, fd, 4);
	if ((nbr = bytes_to_uint(size->str, 4)) > CHAMP_MAX_SIZE)
		ft_panic(1, "Champion size is too big (%u)\n", nbr);
	clean_t_line(&size);
	return (nbr);
}

/*
** Parse padding, which takes 4 bytes and evaluates to 0
*/

void			parse_padding(char *filename, int fd)
{
	t_line			*pad;
	unsigned int	nbr;

	pad = read_n_bytes(filename, fd, 4);
	if ((nbr = bytes_to_uint(pad->str, 4)) != 0)
		ft_panic(1, "Padding is invalid. Should be zero, %d instead.\n", nbr);
	clean_t_line(&pad);
}

/*
** Read and validate header
*/

t_header	*read_header(char *filename, int fd)
{
	t_header		*header;
	char			*tmp;

	header = ft_memalloc(sizeof(t_header));
	header->magic = parse_magic(filename, fd);
	ft_strcpy(header->name, (tmp = parse_name(filename, fd)));
	ft_strdel(&tmp);
	parse_padding(filename, fd);
	header->size = parse_size(filename, fd);
	ft_strcpy(header->comment, (tmp = parse_comment(filename, fd)));
	ft_strdel(&tmp);
	parse_padding(filename, fd);
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
