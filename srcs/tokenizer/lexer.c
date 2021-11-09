/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:24:17 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:39:36 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* input: the command line, a char *.
 * output: a list of tokens
*/

t_list	*tokenizer(char *line)
{
	char					*cursor;
	t_list					*token_list;
	enum e_machine_states	state;
	t_buffer				buffer;
	int						i;

	initialize_variables(&state, &token_list);
	initialize_buffer(&buffer);
	if (line == NULL || buffer.buf == NULL)
		return (FAIL);
	cursor = line;
	i = ft_strlen(line);
	while (i-- >= 0)
	{
		if (analyzer(*cursor, &state, &token_list, &buffer) == FAIL)
		{
			ft_lstclear(&token_list, free_token);
			g_global.ret = 258;
			token_list = NULL;
			break ;
		}
		cursor++;
	}
	free(buffer.buf);
	return (token_list);
}

t_error	analyzer(char cursor, enum e_machine_states *state, \
		t_list **token_list, t_buffer *buffer)
{
	t_error	check;

	t_error (*f[NUM_OF_STATES])(char cursor, enum e_machine_states *state, \
		t_list **token_list, t_buffer *buffer);
	if (!state || !token_list || !buffer)
		return (FAIL);
	f[ST_TRANSITION] = f_transition;
	f[ST_IN_WORD] = f_inword;
	f[ST_OPEN_DQUOTE] = f_doublequote;
	f[ST_OPEN_SQUOTE] = f_singlequote;
	f[ST_LESS] = f_less;
	f[ST_GREAT] = f_great;
	f[ST_SUBSTITUTION] = f_var_substitution;
	f[ST_SUBSTIT_DQUOTE] = f_var_substit_dquote;
	check = (*f[*state])(cursor, state, token_list, buffer);
	return (check);
}

void	set_machine_state(char cursor, enum e_machine_states *state)
{
	if (ft_isspace(cursor))
		*state = ST_TRANSITION;
	else if (cursor == '<')
		*state = ST_LESS;
	else if (cursor == '>')
		*state = ST_GREAT;
	else if (cursor == '"')
		*state = ST_OPEN_DQUOTE;
	else if (cursor == '\'')
		*state = ST_OPEN_SQUOTE;
	else if (cursor == '|')
		*state = ST_TRANSITION;
	else if (cursor == '$')
		*state = ST_SUBSTITUTION;
	else
		*state = ST_IN_WORD;
}

void	initialize_variables(enum e_machine_states *state, t_list **token_list)
{
	if (!state || !token_list)
		return ;
	*state = ST_TRANSITION;
	*token_list = NULL;
}
