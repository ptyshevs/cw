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
	unsigned int map[MEM_SIZE]; // Memory is circular, thus map[k] = map[MEM_SIZE + k]
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
	unsigned int	pos; // same as PC?
	unsigned int	carry; // flag that tells if the latest operation was successful
	unsigned int	id; // Number of the player that have created it
	unsigned int	reg[REG_NUMBER]; // register
	t_bool			alive;
}				t_proc;

typedef struct	s_op
{
	char			*name;
	unsigned int	nargs;
	unsigned int	args[16];
	unsigned int	op;
	unsigned int	cycles;
	char			*description;
	unsigned int	codage;
	unsigned int	carry;
}				t_op;


#endif
