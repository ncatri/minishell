/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:59 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:27:00 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_error	initialize_buffer(t_buffer *buf)
{
	buf->buf = ft_calloc(sizeof(char), BUF_SIZE);
	buf->size = BUF_SIZE;
	buf->pos = 0;
	if (buf->buf == NULL)
		return (FAIL);
	return (SUCCESS);
}

t_error	append_buffer(t_buffer *buffer, char c)
{
	char	*tmp;

	if (buffer->pos >= buffer->size)
	{
		tmp = malloc(sizeof(char) * (buffer->size + BUF_SIZE));
		if (!tmp)
		{
			free(buffer->buf);
			return (FAIL);
		}
		ft_memcpy(tmp, buffer->buf, buffer->size);
		buffer->size += BUF_SIZE;
		free(buffer->buf);
		buffer->buf = tmp;
	}
	buffer->buf[buffer->pos] = c;
	buffer->pos++;
	return (SUCCESS);
}

t_error	append_str_to_buffer(t_buffer *buffer, char *str)
{
	while (str && *str)
	{
		if (append_buffer(buffer, *str) == FAIL)
			return (FAIL);
		str++;
	}
	return (SUCCESS);
}
