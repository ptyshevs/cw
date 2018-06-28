/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:07:54 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/17 19:07:59 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Display usage
**
** Invoked when either no arguments were provided, or there is -h option
** specified.
*/

void		show_usage(void)
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles] [-h|--help]"
			"[-v <1|2|3>]"
			"[[-n number] champion1.cor] ...\n");
	exit(1);
}

/*
** Display main info about each bot
*/

void	show_bots(t_bot **bots, unsigned int num_bots)
{
	unsigned int	i;

	i = 0;
	while (i < 0)
	{
		ft_printf("Name: %s\n", bots[i]->header->prog_name);
		ft_printf("Comment: %s\n", bots->header->comment);
		ft_printf("Size: %d\n", bots->header->prog_size);
		ft_printf("Id: %d\n", bots->id);
	}
}

/*
** Log message either to stdout (default behavior) or to fd
*/

void	logging(char *brief, char *standard, char *elaborate)
{
	static	t_verbosity	verbosity = v_standard;
	static	int			fd = 1;

	if ((unsigned long)brief == 42U && verbosity == v_none)
	{
		verbosity = (t_verbosity)standard;
		fd = (int)elaborate;
		return ;
	}
	if (verbosity == v_brief && brief)
		ft_dprintf(fd, "%s\n", brief);
	else if (verbosity == v_standard && standard)
		ft_dprintf(fd, "%s\n", standard);
	else if (verbosity == v_elaborate && elaborate)
		ft_dprintf(fd, "%s\n", elaborate);
	else
		ft_panic(1, "Unrecognized verbosity level (%d) or arguments:"
		"\n%s\n%s\n%s\n", verbosity, brief, standard, elaborate);
}
