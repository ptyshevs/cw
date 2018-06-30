/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 21:53:03 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/29 21:53:10 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Initialize colors for vizualization.
** COLOR_WHITE is grey
** Colors:
**   - 1:
*/

void	init_color_table(void)
{
	start_color(); // allocate color table

	init_pair(1, COLOR_BLACK, COLOR_WHITE); // background
	init_pair(2, COLOR_WHITE, COLOR_BLACK); // map
	init_pair(3, COLOR_GREEN, COLOR_BLACK); // 1st bot
	init_pair(4, COLOR_BLACK, COLOR_GREEN); // 1st bot caret
	init_pair(5, COLOR_BLUE, COLOR_BLACK); // 2nd bot
	init_pair(6, COLOR_BLACK, COLOR_BLUE); // 2nd bot caret
	init_pair(7, COLOR_RED, COLOR_BLACK); // 3rd bot
	init_pair(8, COLOR_BLACK, COLOR_RED); // 3rd bot caret
	init_pair(9, COLOR_CYAN, COLOR_BLACK); // 4th bot
	init_pair(10, COLOR_BLACK, COLOR_CYAN); // 4th bot caret
	init_pair(11, COLOR_RED, COLOR_RED); // pure red for debugging purposes
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
}

/*
** Map color name to number used in attr[on|off]
*/

chtype		get_color(char *color)
{
	static t_col	colors[12] = {{"bg", COLOR_PAIR(1)}, {"map", COLOR_PAIR(2)},
								{"b1", COLOR_PAIR(3)}, {"b1pr", COLOR_PAIR(4)},
								{"b2", COLOR_PAIR(5)}, {"b2pr", COLOR_PAIR(6)},
								{"b3", COLOR_PAIR(7)}, {"b3pr", COLOR_PAIR(8)},
								{"b4", COLOR_PAIR(9)}, {"b4pr", COLOR_PAIR(10)},
								{"debug", COLOR_PAIR(11)}, {"info", COLOR_PAIR(12) | A_BOLD}};
	int				i;

	i = 0;
	while (i < 11)
	{
		if (ft_strequ(colors[i].name, color))
			return (colors[i].c);
		i++;
	}
	return (0);
}

/*
** Return bot color by index
*/

chtype	get_bot_color_by_index(int index, t_bool foreground)
{
	if (index == 0)
		return (foreground ? get_color("b1") : get_color("b1pr"));
	else if (index == 1)
		return (foreground ? get_color("b2") : get_color("b2pr"));
	else if (index == 2)
		return (foreground ? get_color("b3") : get_color("b3pr"));
	else if (index == 3)
		return (foreground ? get_color("b4") : get_color("b4pr"));
	else
		ft_panic(1, "Unknown id\n");
	return (0);
}

/*
** Get process color
*/

int		get_proc_color(t_map *map, int id)
{
	static int colors[4] = {COLOR_PAIR(4), COLOR_PAIR(6),
							COLOR_PAIR(8), COLOR_PAIR(10)};
	int		i;

	i = 0;
	while (i < 4)
	{
		if (map->bot_ids[i] == id)
			return (colors[i]);
		i++;
	}
//	ft_panic(1, "get_proc_color with unrecognized id: %d\n", id);
	return (0);
}

