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

#include <curses.h>
# include "libft.h"
# include "op.h"

typedef unsigned int	t_uint;
struct					s_viz;

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
*/

typedef enum	e_vrb
{
	v_essential,
	v_alive,
	v_cycles = 2,
	v_ops = 4,
	v_deaths = 8,
	v_pc = 16,
	v_mouse = 32,
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
** Map structure
** Fields:
**    - map: circular arena, so map[k] = map[MEM_SIZE + k] = map[MEM_SIZE - k]
**    - n_bots: number of bots on the map
**    - bots: structures for representing bots
**    - n_proc: number of processes currently active
**    - procs: list of all processes
**    - cycle: variable for storing current cycle
**    - game_cycles: regulates game flow
**    - log: logging structure
**    - viz: whether vizualization mode is ON or OFF
*/

typedef struct	s_map
{
	t_uc			map[MEM_SIZE]; // Memory is circular, thus map[k] = map[MEM_SIZE + k]
	chtype			cmap[MEM_SIZE]; // Map copy for storing colors
	t_uint			n_bots;
	int				*bot_ids;
	t_bot			*bots[MAX_PLAYERS];

	t_uint			n_proc;
	t_proc			*procs;

	int				cyc_cnt; // this is indicator of current cycle
	int				cyc_cur; // this regulates game loop
	int				n_checks;
	int				lives_cur; // current total value of lives
	int				last_alive_i; // index of the last bot declared alive
	t_bool			viz_mode; // the last argument wins
	t_bool			colorful; // whether memory dump should be using colors
	t_bool			game_over;
	t_log			*log;
	struct s_viz	*viz;
	t_pref			*pref;
	t_dump			*dump;
}				t_map;

#endif
