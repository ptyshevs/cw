/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 12:27:58 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 12:30:14 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_tell.h>
#include <ft_printf.h>
#include <ft_str.h>
#include <fcntl.h>
#include "cw.h"

/*
** Display usage and exit with return code 1
*/

void	asm_usage(void)
{
	ft_dprintf(2, "Usage: ./asm [-a] <sourcefile.s>\n");
	ft_dprintf(2, "\t-a : Instead of creating a .cor file, outputs a stripped "
	"and annotated version of the code to the standard output\n");
	exit(1);
}

/*
** filename of format <filename>.s, must be converted to <filename.cor
*/

char	*change_extension(char *filename, char *extension)
{
	(void)filename;
	(void)extension;
	return (NULL); // Nothing here yet
}

void	open_files(t_asm *a)
{
	char	*new_filename;

	if ((a->fd_from = open(a->filename, O_RDONLY)) == -1)
		ft_panic(ft_sprintf("Can't read source file %s", a->filename), 2, 1);
	new_filename = change_extension(a->filename, ".s");
	if ((a->fd_to = open(new_filename, O_WRONLY|O_CREAT)) == -1)
		ft_panic(ft_sprintf("Cant write champion to %s", new_filename), 2, 1);
}

/*
** Handle end of execution properly
*/

void	wrap_up(t_asm *asms)
{
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

	i = 0;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-a"))
			asms.to_stdout = TRUE;
		else
			asms.filename = av[i];
	}
	return (asms);
}

int main(int ac, char **av)
{
	t_asm	asms;

	if (ac == 1)
		asm_usage();
	asms = parse_cli(ac, av);
	open_files(&asms);
	ft_printf("%s: %d\n", asms.filename, asms.to_stdout);
}