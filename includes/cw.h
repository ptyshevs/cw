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

typedef struct	s_bot
{
	unsigned char	*code;
	unsigned int	id;
	t_header		*header;
}				t_bot;


typedef struct	s_map
{
	unsigned char	map[MEM_SIZE]; // Memory is circular, thus map[k] = map[MEM_SIZE + k]
	unsigned int	num_players;
	int				v;  // verbosity level
	t_bool			viz; // n-curses mode is ON?
	t_bot			*bots[MAX_PLAYERS];
}				t_map;


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
}				t_proc;

/*
** File processing
*/

unsigned int	bytes_to_uint(const t_uc *bytes, int n);
t_line			*read_n_bytes(const char *filename, int fd, unsigned int n);

unsigned int	parse_magic(char *filename, int fd);
char			*parse_name(char *filename, int fd);
unsigned int	parse_size(char *filename, int fd);
char			*parse_comment(char *filename, int fd);
void			parse_padding(char *filename, int fd);


unsigned char	*read_file(char *file_name);
void			complete_file(char *file_name, t_bot *bot);
char			*find_comment(const unsigned char *file);
char			*check_comment(const char *comment);
t_bot			*create_new_bot(char *filename, unsigned int id);
t_bot			*init_bot(void);
unsigned int	check_magic(unsigned char *magic);
unsigned char	*find_magic(unsigned char *file);
char			*find_name(unsigned char *file);
char			*check_name(char *name);
unsigned char	*find_size(unsigned char *file);
unsigned char	*find_code(unsigned char *file, int file_size, t_bot *bot);
unsigned int	check_size(unsigned char *size);

/*
** Logging and debugging
*/

typedef enum	e_vrb
{
	v_none,
	v_brief,
	v_standard,
	v_elaborate
}				t_vrb;

void	logging(char *brief, char *standard, char *elaborate);

/*
** Display information
*/

void	show_usage(void);
void	show_bots(t_bot **bots, unsigned int num_bots);

/*
** CLI parsing and bot reading
*/

void	parse_cli(t_map *map, int ac, char **av);
void	read_bot(t_map *map, char *filename, unsigned int id);

/*
** Errors
*/

void	invalid_header(char *filename);
void	size_error(char *filename);

#endif
