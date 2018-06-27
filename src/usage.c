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

int				usage(void)
{
	write(1, "Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] \
		[-a] <champion1.cor> <...>\n"
		"-a        : Prints output from 'aff' (Default is to hide it)\n"
"#### TEXT OUTPUT MODE ####################################################\n"
	"-d N      : Dumps memory after N cycles then exits\n"
	"-s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
	"-v N      : Verbosity levels, can be added together to enable several\n"
	"- 0	   : Show only essentials\n"
	"- 1	   : Show lives\n"
	"- 2	   : Show cycles\n"
	"- 4	   : Show operations (Params are NOT litteral ...)\n"
	"- 8	   : Show deaths\n"
	"- 16	   : Show PC movements (Except for jumps)\n"
"#### BINARY OUTPUT MODE ###################################################\n"
	"-b        : Binary output mode for corewar.42.fr\n"
	"--stealth : Hides the real contents of the memory\n"
"#### NCURSES OUTPUT MODE ##################################################\n"
	"-n        : Ncurses output mode\n"
	"--stealth : Hides the real contents of the memory\n"
"###########################################################################\n", 1161);
	return (0);
}
