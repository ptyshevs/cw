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
#include "viz.h"

/*
** Initialize colors for vizualization.
**
** start_color() initiates ncurses color table
** Colors:
**   - 1: white background (used for making a border)
**   - 2: default map mode (white characters on black bg)
**   - 3: main color of the first bot
**   - 4: color of the first bot's caret
**   - 5: main color of the second bot
**   - 6: color of the second bot's caret
**   - 7: main color of the third bot
**   - 8: color of the trird bot's caret
**   - 9: main color of the fourth bot
**   - 10: color of the fourth bot's caret
**   - 11: pure red for debugging purposes
*/

void	init_color_table(void)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_CYAN, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_RED, COLOR_RED);
}

/*
** get color from colortable
*/

chtype	get_ctable(int n)
{
	static t_col	colors[11] = {{"bg", COLOR_PAIR(1)}, {"map", COLOR_PAIR(2)},
								{"b1", COLOR_PAIR(3)}, {"b1pr", COLOR_PAIR(4)},
								{"b2", COLOR_PAIR(5)}, {"b2pr", COLOR_PAIR(6)},
								{"b3", COLOR_PAIR(7)}, {"b3pr", COLOR_PAIR(8)},
								{"b4", COLOR_PAIR(9)}, {"b4pr", COLOR_PAIR(10)},
								{"debug", COLOR_PAIR(11)}};

	return (n > 0 && n <= 11 ? colors[n - 1].c : (t_uint)-1);
}

/*
** Map color name to number used in attr[on|off]
*/

chtype	get_color(char *color)
{
	static t_col	colors[11] = {{"bg", COLOR_PAIR(1)}, {"map", COLOR_PAIR(2)},
								{"b1", COLOR_PAIR(3)}, {"b1pr", COLOR_PAIR(4)},
								{"b2", COLOR_PAIR(5)}, {"b2pr", COLOR_PAIR(6)},
								{"b3", COLOR_PAIR(7)}, {"b3pr", COLOR_PAIR(8)},
								{"b4", COLOR_PAIR(9)}, {"b4pr", COLOR_PAIR(10)},
								{"debug", COLOR_PAIR(11)}};
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
** Get index of the color in the colortable.
*/

short	color_index(chtype col)
{
	static t_col	colors[11] = {{"bg", COLOR_PAIR(1)}, {"map", COLOR_PAIR(2)},
								{"b1", COLOR_PAIR(3)}, {"b1pr", COLOR_PAIR(4)},
								{"b2", COLOR_PAIR(5)}, {"b2pr", COLOR_PAIR(6)},
								{"b3", COLOR_PAIR(7)}, {"b3pr", COLOR_PAIR(8)},
								{"b4", COLOR_PAIR(9)}, {"b4pr", COLOR_PAIR(10)},
								{"debug", COLOR_PAIR(11)}};
	short			i;

	i = 0;
	while (i < 11)
	{
		if (col == colors[i].c)
			return (short)(i + 1);
		i++;
	}
	return (-1);
}

/*
** Return bot color by index
*/

chtype	bot_color(int index, t_bool foreground)
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
** Return bot color by index (text-mode)
*/

char	*bot_strcolor(int index)
{
	static char	*colors[4] = {"{green}", "{blue}", "{red}", "{cyan}"};

	return (index >= 0 && index < 4 ? colors[index] : NULL);
}

/*
** Get process color
*/

int		get_proc_color(t_map *map, int id)
{
	static int	colors[4] = {COLOR_PAIR(4), COLOR_PAIR(6),
							COLOR_PAIR(8), COLOR_PAIR(10)};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (map->bot_ids[i] == id)
			return (colors[i]);
		i++;
	}
	return (0);
}
