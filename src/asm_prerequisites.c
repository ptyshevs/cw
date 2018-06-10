/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_prerequisites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:57:51 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 18:59:55 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_lst.h>
#include "asm.h"

/*
** Display usage and exit with return code 1
*/

static void	asm_usage(void)
{
	ft_dprintf(2, "Usage: ./asm [-a] <sourcefile.s>\n");
	ft_dprintf(2, "\t-a : Instead of creating a .cor file, outputs a stripped "
	"and annotated version of the code to the standard output\n");
	exit(1);
}

/*
** filename of format <filename>.s, must be converted to <filename.cor
*/

static char	*change_extension(char *filename, char *from_ext, char *to_ext)
{
	char	*pos;
	char	*new_filename;

	if (!(pos = ft_strrstr(filename, from_ext)))
		return(ft_strdup(to_ext));
	new_filename = ft_strnew(pos - filename + ft_slen(to_ext));
	ft_strncpy(new_filename, filename, pos - filename);
	ft_strcat(new_filename, to_ext);
	return (new_filename);
}

/*
** Open file to read assembly from and to write bytecode to.
*/

void	open_files(t_asm *a)
{
	char	*new_filename;

	if ((a->fd_from = open(a->name, O_RDONLY)) == -1)
		ft_panic(ft_sprintf("Can't read source file %s", a->name), 2, 1);
	new_filename = change_extension(a->name, ".s", ".cor");
	if ((a->fd_to = open(new_filename, O_WRONLY|O_CREAT, 644)) == -1)
		ft_panic(ft_sprintf("Cant write champion to %s", new_filename), 2, 1);
	ft_strdel(&new_filename);
	a->name = NULL; // need for using gnl later
}

/*
** Handle end of execution properly
*/

void	wrap_up(t_asm *asms)
{
	t_list	*prev;

	while (asms->lines)
	{
		prev = asms->lines;
		asms->lines = asms->lines->next;
		ft_memdel(&prev->content);
		ft_memdel((void **) &prev);
	}
	close(asms->fd_from);
	close(asms->fd_to);
}

/*
** Parse CLI arguments
*/

t_asm	parse_cli(int ac, char **av)
{
	static t_asm	asms;
	int				i;

	if (ac == 1)
		asm_usage();
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-a"))
			asms.to_stdout = TRUE;
		else
			asms.name = av[i];
	}
	return (asms);
}