/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:42:27 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/19 15:42:40 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Convert decimal number to stringified hex version
*/

t_line		*dec_to_hex(int n, unsigned int width)
{
	t_line			*str;
	unsigned int	i;

	str = ft_memalloc(sizeof(t_line));
	str->len = width;
	str->str = ft_memalloc(str->len);
	i = width;
	while (n)
	{
		str->str[i-- - 1] = (t_uc)(n & 0xFF);
		n >>= 8;
	}
	while (i > 0)
		str->str[i-- - 1] = 0;
	return (str);
}

/*
** Write magic to file
*/

void	write_magic(int fd_to)
{
	t_line	*magic;

	magic = dec_to_hex(COREWAR_EXEC_MAGIC, 4);
	write(fd_to, magic->str, magic->len);
	ft_memdel((void **)&magic->str);
	ft_memdel((void **)&magic);
}

/*
** Write bot size to file
*/

void	write_bot_size(int fd_to, int n)
{
	t_line	*size;

	size = dec_to_hex(n, 4);
	write(fd_to, size->str, size->len);
	clean_t_line(&size);
}

/*
** Write bot name to file
*/

void	write_name_comment_size(int fd_to, t_asm *asms)
{
	size_t			i;
	static char		block[COMMENT_LENGTH];

	i = ft_slen(asms->name) - 2;
	write(fd_to, asms->name + 1, i);
	write(fd_to, block, PROG_NAME_LENGTH - i);
	write(fd_to, block, 4); // Padding before bot size
	write_bot_size(fd_to, asms->cum_size);
	i = ft_slen(asms->comment) - 2;
	write(fd_to, asms->comment + 1, i);
	write(fd_to, block, COMMENT_LENGTH - i);
	write(fd_to, block, 4);
}

/*
** Encode instruction and its arguments into hex and output to file
*/

void	write_instruction(int fd_to, t_tk *instr)
{
	(void)fd_to;
	(void)instr;
}


/*
** Write all instructions and their arguments to file
*/

void	write_executable_code(int fd_to, t_list *tokens)
{
	t_tk	*tk;

	while (tokens)
	{
		tk = tokens->content;
		while (tk)
		{
			if (tk->type == INSTRUCTION)
				write_instruction(fd_to, tk);
			tk = tk->next;
		}
		tokens = tokens->next;
	}
}
