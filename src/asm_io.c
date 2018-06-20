/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:59:52 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/11 17:00:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Read file to list (required to perform preliminary lexical analysis),
** ignoring everything after COMMENT_CHAR
*/

void		read_file(int fd_from, t_list **where)
{
	char	*iter;
	char	*tmp;
	size_t	len;

	iter = NULL;
	while (ft_sgnl(fd_from, &iter) > 0)
	{
		if ((tmp = ft_strchr(iter, COMMENT_CHAR)))
		{
			len = tmp - iter;
			tmp = ft_strnew(len);
			ft_strncpy(tmp, iter, len);
			ft_lstappend(where, ft_lstnew(tmp, ft_slen(tmp) + 1));
			ft_strdel(&tmp);
		}
		else if ((tmp = ft_strchr(iter, ';')))
		{
			tmp = ft_strtrunc(iter, tmp - iter, FALSE);
			ft_lstappend(where, ft_lstnew(tmp, ft_slen(tmp) + 1));
			ft_strdel(&tmp);
		}
		else
			ft_lstappend(where, ft_lstnew(iter, ft_slen(iter) + 1));
	}
}

/*
** filename of format <filename>.s, must be converted to <filename.cor
*/

static char	*change_extension(char *filename, char *from_ext, char *to_ext)
{
	char	*pos;
	char	*new_filename;

	if (!(pos = ft_strrstr(filename, from_ext)))
		return (ft_strdup(to_ext));
	new_filename = ft_strnew(pos - filename + ft_slen(to_ext));
	ft_strncpy(new_filename, filename, pos - filename);
	ft_strcat(new_filename, to_ext);
	return (new_filename);
}

/*
** Create *.cor file
*/

void		write_file(t_asm *a, t_list *tokens)
{
	char	*new_filename;
	int		fd_to;

	new_filename = change_extension(a->filename, ".s", ".cor");
	if ((fd_to = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		ft_panic(ft_sprintf("Cant write champion to %s", new_filename), 2, 1);
	header(fd_to, a);
	write_executable_code(fd_to, tokens);
	ft_printf("Writing output program to %s\n", new_filename);
	ft_strdel(&new_filename);
	close(fd_to);
}
