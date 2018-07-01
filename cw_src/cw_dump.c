/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:07:47 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 00:07:59 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

/*
** Dump map state if necessary (text mode and appropriate CLI options specified)
*/

void	dump_if_necessary(t_map *map)
{
	char	*tmp;

	if (map->viz_mode || !map->dump->dump)
		return ;
	if (map->cyc_cur > 0 && map->cyc_cur % map->dump->n == 0)
	{
		if (map->dump->once)
		{
			show_map(map, False);
			exit(0);
		}
		show_map(map, False);
		ft_gnl(0, &tmp);
	}
}
