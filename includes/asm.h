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

typedef struct	s_tk
{
	char		*tk;
	int			line;
	int			chr;
}				t_tk;

t_asm	parse_cli(int ac, char **av);
void	open_files(t_asm *a);
void	read_file(int fd_from, t_list **where);
void	lexical_analysis(t_list *line);

char	*cut_string(t_asm *asms, t_list **lines, char *what);

void	wrap_up(t_asm *asms);


#endif