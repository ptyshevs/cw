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

void	parse_file(char *filename)
{
	(void)filename;
}

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
	ft_printf("%s: %d\n", asms.filename, asms.to_stdout);
}