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

# include "structs.h"
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

/*
** Logging and dumping
*/

void	log_map(t_map *map, t_proc *pr, char *message, ...);
void	to_log(t_map *map, char *message, ...);
void	to_valog(t_map *map, char *message, va_list ap);
void	log_live(t_map *map, t_uint index);
void	log_sti(t_map *map, t_proc *pr, t_uint first_arg, t_uint sec_arg);
void	log_ldi(t_map *map, t_uint pc, t_uint first_arg, t_uint sec_arg);
void	log_fork(t_map *map, t_proc *pr, t_uint new_pc);
void	log_instruction(t_map *map, t_proc *pr);
void	log_move(t_map *map, t_proc *pr, t_uint n);
void	log_reg(t_map *map, t_proc *pr);
void	log_more(t_map *map, char *message, ...);
void	introduce_bots(t_map *map);

void	dump_if_necessary(t_map *map);

/*
** Display information
*/

void	show_usage(void);
void	show_bots(t_bot **bots, t_uint num_bots);
void	show_map(t_map *map, t_bool colorize);
void	show_procs(t_proc *procs);
void	show_args(t_arg *args);

/*
** CLI parsing and bot reading
*/

void	parse_cli(t_map *map, int ac, char **av);
void	read_bot(t_map *map, char *filename, int id, t_bool id_frm_cli);

/*
** Misc useful stuff
*/

t_uint	bytes_to_uint(const t_uc *bytes, t_uint n);
t_line	*read_n_bytes(const char *filename, int fd, t_uint n);
void	collect_ids(t_map *map);
int		p_index_from_id(t_map *map, int id);
t_uint	get_reg(t_proc *pr, t_uint n);
void	set_reg(t_proc *pr, t_uint n, t_uint v);
t_uint	get_ind(t_proc *pr, t_uint v, t_bool is_long);
t_uint	get_indval(t_map *map, t_proc *pr, t_uint ind_v, t_bool is_l);
void	val_to_map(t_map *map, t_proc *pr, t_uint n, t_uint v);
t_uint	get_arg(t_map *map, t_proc *pr, t_uint n, t_bool is_l);

/*
** Bot file parsing
*/

t_uint	parse_magic(char *filename, int fd);
char	*parse_name(char *filename, int fd);
t_uint	parse_size(char *filename, int fd);
char	*parse_comment(char *filename, int fd);
void	parse_padding(char *filename, int fd);

void	clean_bot(t_bot **abot);

/*
** Operations on map
*/

void	set_default_pref(t_map *map);
void	inhabit_map(t_map *map);
t_uint	get_map(t_map *map, int n);
void	set_map(t_map *map, int n, t_uc v, chtype who);
//void	bytes_to_map(t_map *map, t_uint pc, t_uint val, t_uint nbytes);
void	move_proc(t_map *map, t_proc *pr, int n);

/*
** Operations on processes
*/

void	init_procs(t_map *map);

/*
** Instructions
*/

void	i_live(t_map *map, t_proc *pr);
void	i_load(t_map *map, t_proc *pr);
void	i_store(t_map *map, t_proc *pr);
void	i_add(t_map *map, t_proc *pr);
void	i_sub(t_map *map, t_proc *pr);
void	i_and(t_map *map, t_proc *pr);
void	i_or(t_map *map, t_proc *pr);
void	i_xor(t_map *map, t_proc *pr);
void	i_zjmp(t_map *map, t_proc *pr);
void	i_ldi(t_map *map, t_proc *pr);
void	i_sti(t_map *map, t_proc *pr);
void	i_fork(t_map *map, t_proc *pr);
void	i_lload(t_map *map, t_proc *pr);
void	i_lldi(t_map *map, t_proc *pr);
void	i_lfork(t_map *map, t_proc *pr);
void	i_aff(t_map *map, t_proc *pr);

/*
** Operations on arguments
*/

t_arg	*codage_to_args(t_map *map, t_proc *pr, const t_op *instr, t_uint cdg);
t_arg	*instr_to_args(t_map *map, t_proc *pr, const t_op *instr);
t_bool	args_are_valid(const t_op *instr, t_arg *args);
t_uint	args_to_bytes(const t_op *instr, t_arg *args);
t_uint	collect_arg(t_map *map, t_uint size, t_uint pc, t_uint frwd);

/*
** Execution flow
*/

void	exec(t_map *map, t_proc *pr);
t_proc	*create_proc(t_uint id, t_uint pos);
void	add_proc(t_proc **ahead, t_proc *pr);
void	update_procs(t_map *map);
void	game_loop(t_map *map);
void	vgame_loop(t_map *map);
void	handle_period(t_map *map);

/*
** Errors
*/

void	invalid_header(char *filename);
void	size_error(char *filename);


#endif
