/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_viz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 21:51:33 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/29 21:51:50 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"


/*
** Vizualize process
*/

void	vproc(t_map *map, t_viz *viz)
{
	t_proc	*pr;
	int		col;

	pr = map->procs;
	while (pr)
	{
		if (!pr->alive)
			break ;
		col = get_proc_color(map, pr->id);
		wattron(viz->wmap, col);
		mvwprintw(viz->wmap, pr->pc / 64, pr->pc % 64 * 3 + 1, "%02x", map->map[pr->pc]);
		wattroff(viz->wmap, col);
		pr = pr->next;
	}
}

/*
** Vizualize map
*/

void	vmap(t_map *map, t_viz *viz)
{
	static int	colors[4] = {COLOR_PAIR(3), COLOR_PAIR(5),
							COLOR_PAIR(7), COLOR_PAIR(9)};
	t_uint		i;
	t_uint		j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			t_uint m = 0;
			while (m < map->n_bots)
			{
			if (i * 64 + j == map->bots[m]->start_pos)
				wattron(viz->wmap, colors[m]);
			else if (i * 64 + j == map->bots[m]->start_pos + map->bots[m]->header->size)
				wattroff(viz->wmap, colors[m]);
			m++;
		}
			mvwprintw(viz->wmap, i, j * 3, " %02x ", map->map[i * 64 + j]);
			j++;
		}
		i++;
	}
}

/*
* Vizualize bots and live breakdown
*/

void	vbots(t_map *map, t_viz *viz)
{
	t_uint	i;

	i = 0;
	while (i < map->n_bots)
	{
		mvwprintw(viz->winfo, 8 + (i * 4), 1, "Player %d:", map->bots[i]->id);
		wattron(viz->winfo, get_bot_color_by_index(i, True));
		mvwprintw(viz->winfo, 8 + (i * 4), 15, "%s",
				map->bots[i]->header->name);
		wattroff(viz->winfo, get_bot_color_by_index(i, True));
		mvwprintw(viz->winfo, 8 + 1 + (i * 4), 3, "Last live: %d",
				map->bots[i]->last_live);
		mvwprintw(viz->winfo, 8 + 2 + (i * 4), 3, "Lives in current period: %d",
				map->bots[i]->lives);
		i++;
	}
}

/*
** Vizualize info
*/

void	vinfo(t_map *map, t_viz *viz)
{
	wattron(viz->winfo, get_color("info"));
	mvwprintw(viz->winfo, 1, 20, viz->active ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(viz->winfo, 3, 1, "Cycle: %d", map->cyc_cnt);
	mvwprintw(viz->winfo, 4, 25, "Cycles/second limit: %d", viz->cycles_sec);
	mvwprintw(viz->winfo, 4, 1, "Processes: %d", map->n_proc);
	mvwprintw(viz->winfo, 3, 25, "Cycles to die: %d", map->pref.cycles_to_die);
	mvwprintw(viz->winfo, 5, 1, "NBR_LIVE: %d", map->pref.nbr_live);
	mvwprintw(viz->winfo, 5, 25, "Cycles delta: %d", map->pref.cycle_delta);
	mvwprintw(viz->winfo, 6, 1, "MAX_CHECKS: %d", map->pref.max_checks);
	wattroff(viz->winfo, get_color("info"));
}

/*
** Vizualize log - store list of K last messages, redrawing it on every iteration
*/

void	vlog(t_map *map, t_viz *viz)
{
	t_list	*tmp;
	int		i;

	tmp = map->log.log;
	i = map->log.length;
	while (tmp)
	{
		mvwprintw(viz->wlog, i, 1, "%s", tmp->content);
		tmp = tmp->next;
		i -= 1;
	}
}
