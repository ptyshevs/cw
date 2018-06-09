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

# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "ft_str.h"
# include "ft_tell.h"

typedef struct	s_asm
{
	char			*filename;
	t_bool			to_stdout;
	int				fd_from;
	int				fd_to;
}				t_asm;


t_asm	parse_cli(int ac, char **av);
void	open_files(t_asm *a);

void	wrap_up(t_asm *asms);


#endif