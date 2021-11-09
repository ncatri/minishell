/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:27:27 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:27:29 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execution.h"

t_error	f_var_substit_dquote(char cursor, enum e_machine_states *state,
		t_list **token_list, t_buffer *buffer)
{
	static t_buffer	var_buf = {NULL, 0, 0};

	(void)token_list;
	if (cursor == '?')
	{
		if (deal_question_mark(buffer, state) == FAIL)
			return (FAIL);
	}
	else if (ft_isalnum(cursor) || cursor == '_')
		append_buffer(&var_buf, cursor);
	else
	{
		if (deal_variable(buffer, &var_buf) == FAIL)
			return (FAIL);
		if (cursor == '\"')
			*state = ST_IN_WORD;
		else if (cursor == '$')
			;
		else
		{
			append_buffer(buffer, cursor);
			*state = ST_OPEN_DQUOTE;
		}
	}
	return (SUCCESS);
}

t_error	deal_variable(t_buffer *buffer, t_buffer *var_buf)
{
	char	*str;

	if (append_buffer(var_buf, '\0') == FAIL)
		return (FAIL);
	str = my_getenv(var_buf->buf);
	free(var_buf->buf);
	initialize_buffer(var_buf);
	if (append_str_to_buffer(buffer, str) == FAIL)
		return (FAIL);
	free(str);
	return (SUCCESS);
}

t_error	deal_question_mark(t_buffer *buffer, enum e_machine_states *state)
{
	char	*str;

	str = ft_itoa(g_global.ret);
	if (append_str_to_buffer(buffer, str) == FAIL)
		return (FAIL);
	free(str);
	*state = ST_OPEN_DQUOTE;
	return (SUCCESS);
}
