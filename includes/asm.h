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

/*
** Flags enum
*/

typedef enum	e_fl
{
	DUMP_STDOUT = 1,
	DEBUG = 2
}				t_fl;

typedef struct	s_asm
{
	t_fl			flags;

	t_list			*lines;

	char			*name;
	char			*comment;

	int				fd_from;
	int				fd_to;
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
	COMMAND,
	ENDLINE,
	END
}				t_type;

typedef struct	s_tk
{
	char			*tk;
	t_type			type;
	int				line;
	int				chr;
	unsigned int	size;
	unsigned int	codage;
	struct s_tk		*next;
}				t_tk;

/*
** IO-operations
*/

t_asm		parse_cli(int ac, char **av);
void		open_files(t_asm *a);
void		read_file(int fd_from, t_list **where);
void		write_file(t_asm *a, t_list *commands);

/*
** Tokenize the file content
*/

t_list		*tokenize(t_list *lines);
void		release_tokens(t_list **atokens);

t_list		*validate(t_asm *asms, t_list *line);

t_tk		*create_token(char *tk, int line_pos, int chr_pos, t_type type);
void		tk_append(t_tk **atokens, t_tk *tk);

/*
** Cut into token structure
*/

t_tk		*cut_string(t_list **lines, int *start, int *line_nbr);
t_tk		*cut_direct(char *line, int *start, int line_nbr);
t_tk		*cut_direct_label(char *line, int *start, int line_nbr);
t_tk		*cut_register(char *line, int *start, int line_nbr);
t_tk		*cut_separator(char *line, const int *start, int line_nbr);
t_tk		*cut_label(char *line, int *start, int line_nbr);
t_tk		*cut_spec(char *line, int *start, int line_nbr);
t_tk		*cut_indirect(char *line, int *start, int line_nbr);
t_tk		*cut_indirect_label(char *line, int *start, int line_nbr);
t_tk		*cut_instruction(char *line, int *start, int line_nbr);

/*
* Checks
*/

t_bool		is_label(char *line, int start, int line_nbr);
t_bool		is_register(char *line, int start);
t_bool		is_indirect(char *line, int start);
t_bool		is_parameter(t_type type);

/*
** Validation
*/

void		check_name_comment(t_asm *asms, t_list *tokens);
void		check_instructions(t_list *tokens);
const t_op	*find_instruction(t_tk *instr);

/*
** Label dereferencing and size calculation
*/

void	rec_instr_size(t_tk *instr, const t_op *op);
void	rec_codage(t_tk *instr, const t_op *op);
void	label_deref(t_list *tokens);

/*
** Errors
*/

void		lexical_error(int line, int chr);
void		syntax_error_tk(t_tk *tk);
void		syntax_error(char *token, char *type, int line, int chr);
void		instruction_error(char *instruction, int line, int chr);
void		parameter_error(t_tk *instr, t_tk *param, int pos);
void		parameter_count_error(t_tk *instr);
void		unexpected_eof_error(void);
t_bool		duplicate_error(t_tk *cmd);
void		error(int exit_value, char *format, ...);

/*
** Show tokens
*/

void		iter_tokens(t_list *tokens);
char		*tk_type_to_str(t_type type);
char		*tk_type_to_lstr(t_type type);

void		wrap_up(t_asm *asms);

#endif