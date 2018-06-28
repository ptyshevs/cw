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

t_uc	*read_code(char *filename, int fd, unsigned int size)
{
	t_line	*code;
	t_uc	*code_only;

	code = read_n_bytes(filename, fd, size);
	code_only = code->str;
	ft_memdel((void **)&code);
	ssize_t tmp;
	if ((tmp = read(fd, code_only, 10000)) != 0)
		size_error(filename);
	return (code_only);
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

/*
** Create new bot alongside with validating successfully opened file
*/

t_bot			*create_new_bot(char *filename, unsigned int id)
{
	t_bot	*bot;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_panic(1, "Can't read source file %s\n", filename);
	bot = ft_memalloc(sizeof(t_bot));
	bot->id = id;
	bot->header = read_header(filename, fd);
	bot->code = read_code(filename, fd, bot->header->size);
	return (bot);
}
