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

typedef struct	s_map
{
	unsigned int map[MEM_SIZE];
}				t_map;

typedef struct	s_bot
{
	char			*name;
	char			*comment;
	unsigned int	size;
	unsigned int	id;
}				t_bot;

typedef struct	s_proc
{
	unsigned int	pos;
	unsigned int	carry;
	unsigned int	id; // Number of the player that have created it
	unsigned int	reg[16]; // register
	t_bool			alive;
}				t_proc;

typedef struct	s_op
{
	char			*name;
	unsigned int	nargs;
	unsigned int	args[nargs];
	unsigned int	op;
	unsigned int	cycles;
	char			*description;
	unsigned int	codage;
	unsigned int	carry;
}				t_op;

#endif
