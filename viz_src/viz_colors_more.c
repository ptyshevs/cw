/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_colors_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 01:09:30 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/07 01:10:01 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"
#include "viz.h"

/*
** Get index of the color in the colortable.
*/

short	color_index(t_viz *viz, chtype col)
{
	short			i;

	i = 0;
	while (i < viz->col_table_size)
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

chtype	bot_color(t_map *map, int index)
{
	if (!map->viz_mode)
		return (chtype)(index);
	if (index == 0)
		return (get_color(map->viz, "bot1"));
	else if (index == 1)
		return (get_color(map->viz, "bot2"));
	else if (index == 2)
		return (get_color(map->viz, "bot3"));
	else if (index == 3)
		return (get_color(map->viz, "bot4"));
	else
		log_more(map, "bot_color was called with bad index: %d\n", index);
	return (0);
}

chtype	bot_color_id(t_map *map, int id)
{
	return (bot_color(map, p_index_from_id(map, id)));
}

/*
** Return inverse of bot color
*/

chtype	color_inv(t_map *map, int index)
{
	return (get_ctable(map->viz,
				color_index(map->viz, bot_color(map, index)) + 2));
}

/*
** Return bot color by index (text-mode)
*/

char	*bot_strcolor(int index)
{
	static char	*colors[4] = {"{green}", "{blue}", "{red}", "{cyan}"};

	return (index >= 0 && index < 4 ? colors[index] : NULL);
}
