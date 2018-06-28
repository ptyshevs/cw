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
# include "libft.h"
# include "ft_printf.h"
# include "ft_gnls.h"
# include "ft_memory.h"
# include "ft_str.h"
# include "ft_strnum.h"
# include "ft_tell.h"
# include <fcntl.h>

typedef unsigned int t_uint;

typedef struct	s_bot
{
	unsigned int	start_pos;
	unsigned char	*code;
	int				id;
	t_header		*header;
}				t_bot;

/*
** Process - the same as caret
*/

typedef struct	s_proc
{
	unsigned int	pc; // process position
	unsigned int	carry; // flag that tells if the latest operation was successful
	unsigned int	id; // Number of the player that have created it
	unsigned int	reg[REG_NUMBER]; // register
	t_bool			alive;
	struct s_proc	*next;
}				t_proc;

typedef enum	e_vrb
{
	v_none,
	v_brief,
	v_full
}				t_vrb;


typedef struct	s_log
{
	t_vrb		level;
	int			to;
}				t_log;

typedef struct	s_map
{
	unsigned char	map[MEM_SIZE]; // Memory is circular, thus map[k] = map[MEM_SIZE + k]

	unsigned int	n_bots;
	t_bot			*bots[MAX_PLAYERS];

	unsigned int	n_proc;
	t_proc			*procs;

	int				cycles;

	t_log			log;
	t_bool			viz; // n-curses mode is ON?
}				t_map;

/*
** Logging and debugging
*/


void	logging(t_log log, char *brief, char *full);
void	log_this(t_log log, char *message, ...);

/*
** Display information
*/

void	show_usage(void);
void	show_bots(t_bot **bots, unsigned int num_bots);
void	show_map(t_map *map);
void	show_procs(t_proc *procs);

/*
** CLI parsing and bot reading
*/

void			parse_cli(t_map *map, int ac, char **av);
void			read_bot(t_map *map, char *filename,
						int id, t_bool id_frm_cli);

unsigned int	bytes_to_uint(const t_uc *bytes, unsigned int n);
t_line			*read_n_bytes(const char *filename, int fd, unsigned int n);

unsigned int	parse_magic(char *filename, int fd);
char			*parse_name(char *filename, int fd);
unsigned int	parse_size(char *filename, int fd);
char			*parse_comment(char *filename, int fd);
void			parse_padding(char *filename, int fd);

void			clean_bot(t_bot **abot);

/*
** Operations on map
*/

void	inhabit_map(t_map *map);

/*
** Operations on proc
*/

void	init_procs(t_map *map);

/*
** Errors
*/

void	invalid_header(char *filename);
void	size_error(char *filename);

#endif
