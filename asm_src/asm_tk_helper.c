/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tk_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptyshevs <ptyshevs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 19:31:23 by ptyshevs          #+#    #+#             */
/*   Updated: 2018/06/14 19:31:52 by ptyshevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Append line tokens to the list of tokens
*/

void	tk_append(t_tk **atokens, t_tk *tk)
{
	t_tk	*tmp;

	if (!tk)
		return ;
	if (!*atokens)
		*atokens = tk;
	else
	{
		tmp = *atokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tk;
	}
}

/*
**  Create a token structure.
**
**  [!] Don't release the <tk>! It is not duplicated, but is used as-is.
** @param tk
** @param line_pos
** @param chr_pos
** @param type
** @return
*/

t_tk	*create_token(char *tk, int line_pos, int chr_pos, t_type type)
{
	t_tk	*token;

	token = ft_memalloc(sizeof(t_tk));
	token->tk = tk;
	token->line = line_pos;
	token->chr = chr_pos;
	token->type = type;
	if (type == REGISTER)
		token->size = T_REG;
	else if (type == DIRECT || type == DIRECT_LABEL)
		token->size = T_DIR;
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		token->size = T_DIR;
	return (token);
}

/*
** Clear the memory allocated for the list of tokenized lines
*/

void	release_tokens(t_list **atokens)
{
	t_list	*tmp;
	t_list	*prev;
	t_tk	*tk;
	t_tk	*tk_prev;

	tmp = *atokens;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		tk = prev->content;
		while (tk)
		{
			tk_prev = tk;
			tk = tk->next;
			ft_strdel(&tk_prev->tk);
			ft_memdel((void **)&tk_prev);
		}
		ft_memdel((void **)&prev);
	}
	*atokens = NULL;
}

/*
** Check if line that contains COMMENT_CHAR or STRANGE_CHAR has this char inside
** double-quotes. If not, we discard comment completely. If it is, it's part of
** the string.
*/

t_bool	is_inside_string(char *line)
{
	char	*open_quote;
	char	*hash;
	char	*strange;
	char	*comment;

	if (!(open_quote = ft_strchr(line, '"')))
		return (False);
	hash = ft_strchr(line, COMMENT_CHAR);
	strange = ft_strchr(line, STRANGE_CHAR);
	if (hash && strange)
		comment = hash < strange ? hash : strange;
	else
		comment = hash ? hash : strange;
	return (t_bool)(comment > open_quote);
}
