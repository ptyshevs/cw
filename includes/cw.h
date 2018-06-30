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
void	introduce_bots(t_map *map);

void	dump_if_necessary(t_map *map);

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
void			collect_ids(t_map *map);

/*
** Bot file parsing
*/

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


#endif
