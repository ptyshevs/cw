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
#include "viz.h"

/*
** Vizualize process
*/

void	vproc(t_map *map, t_viz *viz)
{
	t_proc	*pr;
	int	col;

	pr = map->procs;
	while (pr)
	{
		if (map->cmap[pr->pc] == UINT32_MAX)
			col = COLOR_PAIR(1);
		else
			col = get_ctable(color_index(map->cmap[pr->pc]) + 1);
		wattron(viz->wmap, col);
		mvwprintw(viz->wmap, pr->pc / 64, pr->pc % 64 * 3 + 1,
				"%02x", map->map[pr->pc]);
		wattroff(viz->wmap, col);
		pr = pr->next;
	}
}

/*
** Vizualize map
*/

void	vmap(t_map *map, t_viz *viz)
{
	t_uint		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (map->cmap[i] != UINT32_MAX)
			wattron(viz->wmap, map->cmap[i]);
		mvwprintw(viz->wmap, i / 64, i % 64 * 3, " %02x ", map->map[i]);
		if (map->cmap[i] != UINT32_MAX)
			wattroff(viz->wmap, map->cmap[i]);
		i++;
	}
}

/*
** Vizualize information on players
*/

void	vbots(t_map *map, t_viz *viz)
{
	t_uint	i;

	i = 0;
	while (i < map->n_bots)
	{
		mvwprintw(viz->winfo, 8 + (i * 4), 1, "Player %d:", map->bots[i]->id);
		wattron(viz->winfo, bot_color(i, True));
		mvwprintw(viz->winfo, 8 + (i * 4), 15, "%s",
				map->bots[i]->header->name);
		wattroff(viz->winfo, bot_color(i, True));
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
	mvwaddstr(viz->winfo, 1, 20, viz->active ? "**RUNNING**" : "**PAUSED**");
	mvwprintw(viz->winfo, 3, 1, "Cycle: %d", map->cyc_cnt);
	mvwprintw(viz->winfo, 4, 1, "Processes: %d", map->n_proc);
	mvwprintw(viz->winfo, 3, 25, "Cycles to die: %d", map->pref->cycles_to_die);
	mvwprintw(viz->winfo, 5, 1, "NBR_LIVE: %d", map->pref->nbr_live);
	mvwprintw(viz->winfo, 4, 25, "Cycles delta: %d", map->pref->cycle_delta);
	mvwprintw(viz->winfo, 5, 25, "Cycles/second limit: %d", viz->max_cyc_sec);
	mvwprintw(viz->winfo, 6, 1, "MAX_CHECKS: %d", map->pref->max_checks);
	mvwprintw(viz->winfo, 6, 25, "Cycles/sec: %f", viz->cyc_sec);
	wattroff(viz->winfo, get_color("info"));
}

/*
** Vizualize log - store list of K last messages, redraw it on every iteration
*/

void	vlog(t_map *map, t_viz *viz)
{
	t_log	*log;
	int		i;
	int		j;

	log = map->log;
	i = 0;
	j = log->length - 1;
	while (i < log->cur_length)
	{
		mvwaddstr(viz->wlog, j - 1, 1, log->log[i]);
		i++;
		j -= (int)(ft_slen(log->log[i]) / log->width + 1);
	}
}
