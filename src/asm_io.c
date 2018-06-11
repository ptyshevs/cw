/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:59:52 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/11 17:00:00 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Read file to list (required to perform preliminary lexical analysis),
** ignoring everything after COMMENT_CHAR
*/

void	read_file(int fd_from, t_list **where)
{
	char	*iter;
	char	*tmp;
	size_t	len;

	iter = NULL;
	while (ft_sgnl(fd_from, &iter) > 0)
	{
		if ((tmp = ft_strchr(iter, COMMENT_CHAR)))
		{
			len = tmp - iter;
			tmp = ft_strnew(len);
			ft_strncpy(tmp, iter, len);
			ft_lstappend(where, ft_lstnew(tmp, ft_slen(tmp) + 1));
			ft_strdel(&tmp);
		}
		else
			ft_lstappend(where, ft_lstnew(iter, ft_slen(iter) + 1));
	}
}

// add writing to file here