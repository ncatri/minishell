/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:27:20 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:27:21 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(enum e_token_types type, char *buf)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token)
	{
		token->type = type;
		token->data = ft_strdup(buf);
		if (token->data == NULL)
			return (NULL);
	}
	return (token);
}

void	free_token(void *token)
{
	t_token	*tok;

	tok = (t_token *)token;
	free(tok->data);
	free(tok);
}

t_error	add_token_to_list(t_list **token_list, int token_type, char *data)
{
	t_token	*token;
	t_list	*node;

	token = new_token(token_type, data);
	if (!token)
		return (FAIL);
	node = ft_lstnew(token);
	if (!node)
		return (FAIL);
	ft_lstadd_back(token_list, node);
	return (SUCCESS);
}

t_error	push_buf_to_toklist(t_buffer *buffer, t_list **token_list, \
		enum e_token_types tok_type)
{
	if (buffer->pos == 0)
		return (SUCCESS);
	append_buffer(buffer, '\0');
	if (add_token_to_list(token_list, tok_type, buffer->buf) == FAIL)
		return (FAIL);
	free(buffer->buf);
	initialize_buffer(buffer);
	return (SUCCESS);
}
