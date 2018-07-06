/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 00:46:52 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/07/01 00:47:07 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <curses.h>
# include <zconf.h>
# include "libft.h"
# include "op.h"

typedef unsigned int	t_uint;

/*
** Bot structure
** Fields:
**   - start_pos: Map position from which executable code of this bot begins
**   - code: executable code, size of which is stored in header->size
**   - id: id of the bot (either order in CLI argument list, or manual)
**   - last_live: cyc_cnt value at the moment of last <live> executed with
**       bot->id argument
**   - lives: number of live executed in current period
**   - header: t_header structure, containing name, comment, and size
*/

typedef struct	s_bot
{
	t_uint			start_pos;
	t_uc			*code;
	int				id;
	int				last_live;
	int				lives;
	t_header		*header;
}				t_bot;

/*
** Instruction argument
** Fields:
**   - code [1, 3]: 2 bits from codage that indicate type of argument
**   - type [1, 4]: value used to represent T_* type
**   - size [1, 4]: size of T_* type in bytes
*/

typedef struct	s_arg
{
	t_uc	code;
	t_uc	type;
	t_uc	size;
	t_uint	value;
}				t_arg;

/*
** Process (a.k.a. caret)
** Fields:
**    - pc: caret position on the map. Manipulate only using pc mod MEM_SIZE
**    - carry: flag that tells if the latest operation was successful
**    - id: ID of bot that have spawned this process
**    - reg: registry
**    - cur_cycle: current cycle (used for charging phase)
**    - cur_ins: current instruction being executed
**    - index: unique index of the process
**    - alive: is process alive
**    - next: pointer to the next process (so we create linked list from it)
*/

typedef struct	s_proc
{
	t_uint			pc;
	t_uint			carry;
	t_uint			id;
	t_uint			reg[REG_NUMBER];
	t_uint			cur_cycle;
	const t_op		*cur_ins;
	t_arg			*args;
	t_uint			index;
	int				last_live;
	t_bool			alive;
	t_bool			jumped;
	struct s_proc	*next;
}				t_proc;

/*
** Enumerate type for different verbosity levels
** Fields:
**    - v_essential: bot introduction and winner announcement
**    - v_alive: show more info on live instructions
**    - v_cycles: show current cycle (e.g. It is now cycle 1243)
**    - v_ops: show operations performed (e.g. P    1 | st 01 r1 r2)
**    - v_deaths: show when process dies
**    - v_pc: show movement of caret
**    - v_keys: show keys pressed
**    - v_reg: show registry content when instruction is performed
**    - v_args: show arguments of the instruction being performed
**    - v_more: show even more info
*/

typedef enum	e_vrb
{
	v_essential,
	v_alive,
	v_cycles = 2,
	v_ops = 4,
	v_deaths = 8,
	v_pc = 16,
	v_keys = 32,
	v_reg = 64,
	v_args = 128,
	v_more = 256
}				t_vrb;

/*
** Structure used for managing logging options
** Fields:
**    - level: level of verbosity
**    - to: FD to which log should be written
*/

typedef struct	s_log
{
	t_vrb		level;
	t_bool		identical;
	int			to;
	char		**log;
	int			cur_length;
	int			length;
	int			width;
}				t_log;

/*
** Dump structure
*/

typedef struct	s_dump
{
	t_bool	dump;
	t_bool	once;
	int		n;
}				t_dump;

/*
** Corewar preferences
*/

typedef struct	s_pref
{
	int		cycles_to_die;
	t_uint	cycle_delta;
	t_uint	nbr_live;
	t_uint	max_checks;
}				t_pref;

/*
** Color structure
** Fields:
**   - name: color name (e.g. bot, map, debug)
**   - c: chtype returned by COLOR_PAIR(n) macro
**   - n: color table index (n in COLOR_PAIR(n))
*/

typedef struct	s_col
{
	char	*name;
	chtype	c;
	int		n;
}				t_col;

/*
** Structure for special places on the map
** Fields:
**    - col: color
**    - i: map position
**    - n_cycles: how many cycles it should be shown?
*/

typedef struct	s_special
{
	chtype				col;
	int					i;
	int					n_cycles;
	struct s_special	*next;
}				t_special;

typedef struct	s_song
{
	char	*name;
	char	*filename;
}				t_song;

/*
** Structure for vizualization
** Fields:
**    - h_main: height of the main window
**    - w_main: width of the main window
**    - wmain: main window
**    - wmap: map window
**    - winfo: information window
**    - wlive: live breakdown window
**    - wlog: logging window
**
**    - br: breakdown of lives for the current period
**    - prev_br: breakdown for the previous period
**    - active: whether viz is running or paused
**    - max_cyc_sec: max cycles per second
**    - cyc_sec: current cycles per second ratiofaffadfd
*/

typedef struct	s_viz
{
	int				h_main;
	int				w_main;

	WINDOW			*wmain;
	WINDOW			*wmap;
	WINDOW			*winfo;
	WINDOW			*wlive;
	WINDOW			*wlog;

	pthread_t		vizthr;
	t_special		*spec;
	int				*br;
	int				*prev_br;
	int				col_table_size;
	t_col			*col_table[22];
	t_bool			active;
	t_bool			sound;
	t_bool			playing;
	int				max_cyc_sec;
	double			cyc_sec;
}				t_viz;

/*
** Map structure
** Fields:
**    - map: circular arena, so map[k] = map[MEM_SIZE + k] = map[MEM_SIZE - k]
**    - cmap: map copy of colors associated with each cell
**    - n_bots: number of bots on the map
**    - bot_ids: array of bot ids
**    - bots: structures for representing bots
**
**    - n_proc: number of processes currently active
**    - procs: list of all processes
**
**    - cyc_cnt: variable for storing current cycle
**    - cyc_cur: cycle of the current period
**    - n_checks: number of checks for lives in the period exceed NBR_LIVE
**    - lives_cur: total number of lives in the current period
**    - last_alive_i: index of the last player alive
**    - viz_mode: whether vizualization is turned on
**    - colorful: whether memory dump should be using colors
**    - game_over: is game over?
**    - log: logging structure
**    - viz: vizualization structure
**    - pref: preferences structure
**    - dump: struct for regulating memory dumping
*/

typedef struct	s_map
{
	t_uc			map[MEM_SIZE];
	chtype			cmap[MEM_SIZE];
	t_uint			n_bots;
	int				*bot_ids;
	t_bot			*bots[MAX_PLAYERS];

	t_uint			n_proc;
	t_proc			*procs;

	int				cyc_cnt;
	int				cyc_cur;
	int				n_checks;
	int				lives_cur;
	int				last_alive_i;
	t_bool			viz_mode;
	t_bool			colorful;
	t_bool			game_over;
	t_log			*log;
	t_viz			*viz;
	t_pref			*pref;
	t_dump			*dump;
}				t_map;

#endif
