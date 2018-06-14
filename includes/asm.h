/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:57:07 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/09 18:59:04 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include  <fcntl.h>
# include   "op.h"
# include  "libft.h"
# include   "ft_gnls.h"
# include  "ft_printf.h"
# include  "ft_str.h"
# include  "ft_tell.h"
# include  "ft_lst.h"

# define CHAR_SET "abcdefghijklmnopqrstuvwxyz_0123456789%,r:-"

typedef struct	s_asm
{
	t_bool			to_stdout;

	t_list			*lines;

	char			*name;
	char			*comment;

	int				fd_from;
	int				fd_to;

	unsigned int	line_cnt;
	unsigned int	chr_cnt;
}				t_asm;

/*
** Type of token
*/

typedef enum	e_type
{
	NONE,
	INSTRUCTION,
	STRING,
	INDIRECT,
	DIRECT,
	REGISTER,
	LABEL,
	SEPARATOR,
	INDIRECT_LABEL,
	DIRECT_LABEL,
	COMMAND
}				t_type;

typedef struct	s_tk
{
	char		*tk;
	t_type		type;
	int			line;
	int			chr;
	struct s_tk	*next;
}				t_tk;

/*
** IO-operations
*/

t_asm	parse_cli(int ac, char **av);
void	open_files(t_asm *a);
void	read_file(int fd_from, t_list **where);

/*
** Tokenizing the input
*/

t_list	*tokenize(t_list *lines);
void	iter_tokens(t_list *tokens);

void	lexical_analysis(t_list *line);

t_tk	*create_token(char *tk, int line_pos, int chr_pos, t_type type);

t_tk	*cut_string(t_list **lines, int *start, int *line_nbr);
t_tk	*cut_direct(char *line, int *start, int line_nbr);
t_tk	*cut_direct_label(char *line, int *start, int line_nbr);
t_tk	*cut_register(char *line, int *start, int line_nbr);
t_tk	*cut_separator(char *line, const int *start, int line_nbr);
t_tk	*cut_label(char *line, int *start, int line_nbr);
t_tk	*cut_spec(char *line, int *start, int line_nbr);
t_tk	*cut_indirect(char *line, int *start, int line_nbr);
t_tk	*cut_instruction(char *line, int *start, int line_nbr);

/*
* Checks
*/

t_bool	is_label(char *line, int start, int line_nbr);
t_bool	is_register(char *line, int start);
t_bool	is_instruction(char *line, int start, int line_nbr);

/*
** Errors
*/

void	syntax_error(t_asm *asms, t_list *lines);
void	lexical_error(int line, int chr);
void	lexical_error_tk(t_tk *tk, int i);

void	wrap_up(t_asm *asms);

#endif