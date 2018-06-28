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
	ft_dprintf(2, "Usage: ./asm [-d] [-a] <sourcefile.s>\n");
	ft_dprintf(2, "\t-d : output debug information\n");
	ft_dprintf(2, "\t-a : Instead of creating a .cor file, outputs a stripped "
	"and annotated version of the code to the standard output\n");
	exit(1);
}

/*
** Open file to read assembly from.
*/

void		open_files(t_asm *a)
{
	if ((a->fd_from = open(a->name, O_RDONLY)) == -1)
		ft_panic(1, "Can't read source file %s\n", a->name);
	a->filename = ft_strdup(a->name);
	a->name = NULL;
}

/*
** Handle end of execution properly
*/

void		wrap_up(t_asm *asms)
{
	t_list	*prev;

	while (asms->lines)
	{
		prev = asms->lines;
		asms->lines = asms->lines->next;
		ft_memdel(&prev->content);
		ft_memdel((void **)&prev);
	}
	close(asms->fd_from);
}

/*
** Parse CLI arguments
*/

t_asm		parse_cli(int ac, char **av)
{
	static t_asm	asms;
	int				i;

	if (ac == 1)
		asm_usage();
	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-a"))
			asms.flags |= DUMP_STDOUT;
		else if (ft_strequ(av[i], "-d"))
			asms.flags |= DEBUG;
		else if (ft_strequ(av[i], "-h"))
			asm_usage();
		else
			asms.name = av[i];
	}
	return (asms);
}
