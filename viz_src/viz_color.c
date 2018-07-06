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
** Add color to vizualization color table
*/

void	add_color(t_viz *viz, char *name, short fg, short bg)
{
	static int	i = 0;

	init_pair((short)(i + 1), fg, bg);
	viz->col_table[i] = ft_memalloc(sizeof(t_col));
	viz->col_table[i]->n = i + 1;
	viz->col_table[i]->name = name;
	viz->col_table[i]->c = (chtype)COLOR_PAIR(i + 1);
	i++;
	viz->col_table_size++;
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
	add_color(viz, "bg", COLOR_BLACK, COLOR_WHITE);
	add_color(viz, "map", COLOR_WHITE, COLOR_BLACK);
	add_color(viz, "bot1", COLOR_GREEN, COLOR_BLACK);
	add_color(viz, "bot1bg", COLOR_BLACK, COLOR_GREEN);
	add_color(viz, "bot1inv", COLOR_WHITE, COLOR_GREEN);
	add_color(viz, "bot2", COLOR_BLUE, COLOR_BLACK);
	add_color(viz, "bot2bg", COLOR_BLACK, COLOR_BLUE);
	add_color(viz, "bot2inv", COLOR_WHITE, COLOR_BLUE);
	add_color(viz, "bot3", COLOR_RED, COLOR_BLACK);
	add_color(viz, "bot3bg", COLOR_BLACK, COLOR_RED);
	add_color(viz, "bot3inv", COLOR_WHITE, COLOR_RED);
	add_color(viz, "bot4", COLOR_CYAN, COLOR_BLACK);
	add_color(viz, "bot4bg", COLOR_BLACK, COLOR_CYAN);
	add_color(viz, "bot4inv", COLOR_WHITE, COLOR_CYAN);
	add_color(viz, "debug", COLOR_RED, COLOR_RED);
}

/*
** get color from colortable
*/

chtype	get_ctable(t_viz *viz, int n)
{
	return (n > 0 && n <= viz->col_table_size ?
			viz->col_table[n - 1]->c : (t_uint) - 1);
}

/*
** Map color name to number used in attr[on|off]
*/

chtype	get_color(t_viz *viz, char *color)
{
	int				i;

	i = 0;
	while (i < viz->col_table_size)
	{
		if (ft_strequ(viz->col_table[i]->name, color))
			return (viz->col_table[i]->c);
		i++;
	}
	return (0);
}
