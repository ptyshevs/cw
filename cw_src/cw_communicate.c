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
** Invoked when either no arguments were provided, or there is -h|--help option
** specified.
*/

void		show_usage(void)
{
	ft_printf("Usage: ./corewar [-d|--dump nbr_cycles] [-h|--help] "
			"[-v|--verbose <1|2|3>] [-z] "
			"[[-n number] champion1.cor] ...\n\n");
	ft_printf("  -d --dump\tDump memory after N cycles then exits\n");
	ft_printf("  -h --help\tDisplay usage\n");
	ft_printf("  -v --verbose\tSet level of logger wordiness\n");
	ft_printf("  -z\t\tVizualization mode\n");
	exit(1);
}

/*
** Display main info about each bot
*/

void	show_bots(t_bot **bots, unsigned int num_bots)
{
	unsigned int	i;

	ft_printf("Format: Bot <index> [id|size]: comment\n");
	i = 0;
	while (i < num_bots)
	{
		ft_printf("Bot %s [%d|%u]: %s\n", bots[i]->header->name,
		bots[i]->id, bots[i]->header->size, bots[i]->header->comment);
		i++;
	}
}

/*
** Log message either to stdout (default behavior) or to fd
*/

void	logging(char *brief, char *standard, char *elaborate)
{
	static	t_vrb	verbosity = v_none;
	static	int		fd = 1;

	if ((unsigned long)brief == 42U && verbosity == v_none)
	{
		verbosity = (t_vrb)standard;
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
