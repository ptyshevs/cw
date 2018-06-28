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
		ft_panic(1, "Can't write champion to %s\n", new_filename);
	write_header(fd_to, a);
	write_executable_code(fd_to, tokens);
	ft_printf("Writing output program to %s\n", new_filename);
	ft_strdel(&new_filename);
	close(fd_to);
}

static void	dump_instruction(int offset, t_tk *instr)
{
	ft_printf("%d\t(%-3d) :\t%s ", offset, instr->size, instr->tk);
	while ((instr = instr->next))
	{
		ft_printf(instr->next->type != ENDLINE ? "\t%s\t" : "\t%s", instr->tk);
		instr = instr->next;
	}
	ft_printf("\n");
}

/*
** Output to STDOUT instead of writing to file
*/

void		dump_to_stdout(t_asm *asms, t_list *tokens)
{
	t_tk	*tk;
	int		offset;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", asms->cum_size);
	ft_printf("Name : %s\n", asms->name);
	ft_printf("Comment : %s\n", asms->comment);
	offset = 0;
	while (tokens)
	{
		tk = tokens->content;
		while (tk)
		{
			if (tk->type == INSTRUCTION)
			{
				dump_instruction(offset, tk);
				offset += tk->size;
			}
			tk = tk->next;
		}
		tokens = tokens->next;
	}
}
