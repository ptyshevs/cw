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

#include <ft_strnum.h>
#include "asm.h"

/*
** Convert decimal number to stringified hex version
*/

void	write_dec_to_hex(int fd_to, int n, unsigned int width)
{
	t_line			*str;
	unsigned int	i;

	str = ft_memalloc(sizeof(t_line));
	str->len = width;
	str->str = ft_memalloc(str->len);
	i = width;
	while (n && i > 0)
	{
		str->str[i-- - 1] = (t_uc)(n & 0xFF);
		n >>= 8;
	}
	while (i > 0)
		str->str[i-- - 1] = 0;
	write(fd_to, str->str, width);
	clean_t_line(&str);
}

/*
** Write header to file
*/

void	header(int fd_to, t_asm *asms)
{
	size_t			i;
	static char		block[COMMENT_LENGTH];

	write_dec_to_hex(fd_to, COREWAR_EXEC_MAGIC, 4); // magic
	i = ft_slen(asms->name) - 2; // bot name
	write(fd_to, asms->name + 1, i);
	write(fd_to, block, PROG_NAME_LENGTH - i);
	write(fd_to, block, 4); // Padding before bot size
	write_dec_to_hex(fd_to, asms->cum_size, 4); // bot size
	i = ft_slen(asms->comment) - 2; // comment
	write(fd_to, asms->comment + 1, i);
	write(fd_to, block, COMMENT_LENGTH - i);
	write(fd_to, block, 4); // padding before executable code
}

/*
** Encode instruction and its arguments into hex and output to file
*/

void	write_instruction(int fd_to, t_tk *instr)
{
	int			nbr;
	const t_op	*op;

	op = find_instruction(instr);
	write_dec_to_hex(fd_to, op->op, 1);
	if (instr->codage)
		write_dec_to_hex(fd_to, instr->codage, 1);
	while ((instr = instr->next))
	{
		nbr = ft_atoi(instr->type == REGISTER || instr->type == DIRECT ?
				instr->tk + 1 : instr->tk);
		write_dec_to_hex(fd_to, nbr, instr->type == DIRECT ?
									op->label_size : instr->size);
		instr = instr->next;
	}
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
