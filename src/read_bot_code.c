/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bot_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 19:06:37 by opokusyn          #+#    #+#             */
/*   Updated: 2018/06/17 19:06:40 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

unsigned char	*find_size(unsigned char *file)
{
	unsigned char	*size;
	int				i;
	int				j;

	size = ft_memalloc(sizeof(char) * 4);
	i = PROG_NAME_LENGTH + 8;
	j = 0;
	while (i < PROG_NAME_LENGTH + 12)
		size[j++] = file[i++];
	return (size);
}

unsigned char	*find_code(unsigned char *file, int file_size, t_bot * bot)
{
	unsigned char	*code;
	unsigned int	i;
	unsigned int	j;

	code = ft_memalloc(sizeof(char) * 3185);
	i = 2191;
	j = 0;
	while (i < 3185)
		code[j++] = file[i++];
	j = 0;
	while (j < bot->size)
		ft_printf("%d|", code[j++]);
	ft_printf("\n");
	return (code);
}

unsigned int	check_size(unsigned char *size)
{
	unsigned int	nbr;
	int				i;

	nbr = 0;
	i = 0;
	while (i < 4)
		nbr = (nbr << 8) + size[i++];
	return (nbr);
}
