/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:50:37 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/28 17:50:42 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Read 4 bytes of magic, validate the cumulative number
*/

unsigned int	parse_magic(char *filename, int fd)
{
	t_line			*magic;
	unsigned int	nbr;

	magic = read_n_bytes(filename, fd, 4);
	nbr = bytes_to_uint(magic->str, (unsigned int)magic->len);
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

	comment = read_n_bytes(filename, fd, COMMENT_LENGTH);
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
	nbr = bytes_to_uint(size->str, 4);
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
