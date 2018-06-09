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

#include "asm.h"

char	*parse_name_comment(t_asm *asms)
{
	int	i;

	while (ft_usgnl(asms->fd_from, &(asms->line)) > 0 && ++asms->line_cnt)
	{
		ft_printf("[TOKEN][%03d:%03d]: %s\n", asms->line_cnt, asms->chr_cnt, asms->line);
		if (ft_startswith(asms->line, "#") || ft_strispaces(asms->line))
			continue ;

	}ft_printf("[TOKEN][%03d:%03d]: %s\n", asms->line_cnt, asms->chr_cnt, asms->line);
	return (NULL);
}

int main(int ac, char **av)
{
	t_asm	asms;

	asms = parse_cli(ac, av);
	open_files(&asms);
	char *name = parse_name_comment(&asms);
	wrap_up(&asms);
}
