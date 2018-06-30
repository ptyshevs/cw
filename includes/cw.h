/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 11:17:49 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 11:19:47 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include "op.h"
# include <ncurses.h>
# include "libft.h"
# include "ft_printf.h"
# include "ft_gnls.h"
# include "ft_memory.h"
# include "ft_str.h"
# include "ft_strnum.h"
# include "ft_tell.h"
# include <fcntl.h>

typedef unsigned int t_uint;


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
**    - alive: is process alive
**    - next: pointer to the next process (so we create linked list from it)
*/

typedef struct	s_proc
{
	t_uint			pc; // process position
	t_uint			carry; // flag that tells if the latest operation was successful
	t_uint			id; // Number of the player that have created it
	t_uint			reg[REG_NUMBER]; // register

	t_uint			cur_cycle;
	const t_op		*cur_ins;
	t_arg			*cur_args;

	t_bool			alive;
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
	v_brief,
	v_full
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
	int			to;
}				t_log;


/*
** Structure used for managing logging options
** Fields:
**    - level: level of verbosity
**    - to: FD to which log should be written
*/

typedef struct	s_viz
{
	t_bool	on;
	int		h_main;
	int		w_main;
	WINDOW	*wmain;
	WINDOW	*wmap;
	WINDOW	*winfo;
	WINDOW	*wlog;
	t_bool	active;
	int		cycles_sec;
}				t_viz;

/*
** Color structure
*/

typedef struct	s_col
{
	char	*name;
	chtype	c;
}				t_col;

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

	t_uint			n_bots;
	int				*bot_ids;
	t_bot			*bots[MAX_PLAYERS];

	t_uint			n_proc;
	t_proc			*procs;

	int				cyc_cnt; // this is indicator of current cycle
	int				cyc_cur; // this regulates game loop

	t_bool			dump;
	t_log			log;
	t_viz			viz;
	t_pref			pref;
}				t_map;



/*
** Logging and debugging
*/

void	logging(t_log log, char *brief, char *full);
void	log_map(t_map *map, t_proc *pr, char *message, ...);
void	log_bot(t_map *map, t_bot *bot);
void	log_this(t_log log, char *message, ...);

/*
** Display information
*/

void	show_usage(void);
void	show_bots(t_bot **bots, unsigned int num_bots);
void	show_map(t_map *map);
void	show_procs(t_proc *procs);
void	show_args(t_arg *args);

/*
** CLI parsing and bot reading
*/

void			parse_cli(t_map *map, int ac, char **av);
void			read_bot(t_map *map, char *filename,
						int id, t_bool id_frm_cli);

unsigned int	bytes_to_uint(const t_uc *bytes, t_uint n);
t_line			*read_n_bytes(const char *filename, int fd, t_uint n);

unsigned int	parse_magic(char *filename, int fd);
char			*parse_name(char *filename, int fd);
unsigned int	parse_size(char *filename, int fd);
char			*parse_comment(char *filename, int fd);
void			parse_padding(char *filename, int fd);

void			clean_bot(t_bot **abot);

/*
** Operations on map
*/

void	set_default_pref(t_map *map);
void	inhabit_map(t_map *map);
t_uint	get_map(t_map *map, t_uint n);
void	set_map(t_map *map, t_uint n, t_uc v);
void	move_proc(t_proc *pr, t_uint n);

/*
** Operations on processes
*/

void	init_procs(t_map *map);
t_bool	any_proc_alive(t_proc *pr);

/*
** Operations on arguments
*/

t_arg	*codage_to_args(const t_op *instr, t_uint codage);
t_arg	*instr_to_args(const t_op *instr);
t_bool	args_are_valid(const t_op *instr, t_arg *args);
t_uint	args_to_bytes(const t_op *instr, t_arg *args);

/*
** Execution flow
*/

void	exec(t_map *map, t_proc *pr);
void	update_procs(t_map *map);

/*
** Errors
*/

void	invalid_header(char *filename);
void	size_error(char *filename);

/*
** Vizualization
*/

void		init_color_table(void);
chtype		get_color(char *color);
int			get_proc_color(t_map *map, int id);
chtype		get_bot_color_by_index(int index, t_bool foreground);

void		init_viz(t_viz *viz);
void		wrapup_viz(t_viz *viz);
void		viz_arena(t_viz *viz, t_map *map);

void		vproc(t_map *map, t_viz *viz);
void		vmap(t_map *map, t_viz *viz);
void		vinfo(t_map *map, t_viz *viz);
void		vbots(t_map *map, t_viz *viz);


#endif
