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

void	add_color(t_viz *viz, int n, char *name, chtype c)
{
	static int	i = 0;

	viz->col_table[i] = ft_memalloc(sizeof(t_col));
	viz->col_table[i]->n = n;
	viz->col_table[i]->name = name;
	viz->col_table[i]->c = c;
	i++;
}

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

void	init_color_table(t_viz *viz)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	add_color(viz, 1, "bg", COLOR_PAIR(1));
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	add_color(viz, 2, "map", COLOR_PAIR(2));
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	add_color(viz, 3, "bot1", COLOR_PAIR(3));
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	add_color(viz, 4, "bot1bg", COLOR_PAIR(4));
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	add_color(viz, 5, "bot2", COLOR_PAIR(5));
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	add_color(viz, 6, "bot2bg", COLOR_PAIR(6));
	init_pair(7, COLOR_RED, COLOR_BLACK);
	add_color(viz, 7, "bot3", COLOR_PAIR(7));
	init_pair(8, COLOR_BLACK, COLOR_RED);
	add_color(viz, 8, "bot3bg", COLOR_PAIR(8));
	init_pair(9, COLOR_CYAN, COLOR_BLACK);
	add_color(viz, 9, "bot4", COLOR_PAIR(9));
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	add_color(viz, 10, "bot4bg", COLOR_PAIR(10));
	init_pair(11, COLOR_RED, COLOR_RED);
	add_color(viz, 11, "debug", COLOR_PAIR(11));
}

/*
** get color from colortable
*/

chtype	get_ctable(t_viz *viz, int n)
{
	return (n > 0 && n <= 11 ? viz->col_table[n - 1]->c : (t_uint)-1);
}

/*
** Map color name to number used in attr[on|off]
*/

chtype	get_color(t_viz *viz, char *color)
{
	int				i;

	i = 0;
	while (i < 11)
	{
		if (ft_strequ(viz->col_table[i]->name, color))
			return (viz->col_table[i]->c);
		i++;
	}
	return (0);
}

/*
** Get index of the color in the colortable.
*/

short	color_index(t_viz *viz, chtype col)
{
	short			i;

	i = 0;
	while (i < 11)
	{
		if (col == viz->col_table[i]->c)
			return (short)(i + 1);
		i++;
	}
	return (-1);
}

/*
** Return bot color by index
*/

chtype	bot_color(t_viz *viz, int index)
{
	if (index == 0)
		return (get_color(viz, "bot1"));
	else if (index == 1)
		return (get_color(viz, "bot2"));
	else if (index == 2)
		return (get_color(viz, "bot3"));
	else if (index == 3)
		return (get_color(viz, "bot4"));
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
