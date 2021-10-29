#include "lexer.h"

t_error	f_less(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	if (ft_isalnum(cursor) || ft_isspace(cursor) || cursor == '\0' || cursor == '"'
			|| cursor == '\'')
	{
		if (add_token_to_list(token_list, LESS, "") == FAIL)
			return (FAIL);
		if (ft_isalnum(cursor))
			append_buffer(buffer, cursor); // need to save the character
		set_machine_state(cursor, state);
	}
	else if (cursor == '<')
	{
		if (add_token_to_list(token_list, DLESS, "") == FAIL)
			return (FAIL);
		*state = ST_TRANSITION;
	}
	else if (cursor == '>')
		printf("syntax error\n");
	else
		printf("non covered case in f_less\n");
	return (SUCCESS);
}

t_error	f_great(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	if (ft_isalnum(cursor) || ft_isspace(cursor) || cursor == '\0' || cursor == '"'
			|| cursor == '\'')
	{
		if (add_token_to_list(token_list, GREAT, "") == FAIL)
			return (FAIL);
		if (ft_isalnum(cursor))
			append_buffer(buffer, cursor); // need to save the character
		set_machine_state(cursor, state);
	}
	else if (cursor == '>')
	{
		if (add_token_to_list(token_list, DGREAT, "") == FAIL)
			return (FAIL);
		*state = ST_TRANSITION;
	}
	else if (cursor == '<')
		printf("syntax error\n");
	else
		printf("non covered case in f_great\n");
	return (SUCCESS);
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
	else if (ft_isascii(cursor))
		*state = ST_IN_WORD;
}

t_error	push_buf_to_toklist(t_buffer *buffer, t_list **token_list, enum e_token_types tok_type)
{
	append_buffer(buffer, '\0');
	if (add_token_to_list(token_list, tok_type, buffer->buf) == FAIL)
		return (FAIL);
	free(buffer->buf);
	initialize_buffer(buffer);
	return (SUCCESS);
}

t_error	expand_buffer_push_toklist(t_buffer *buffer, t_list **token_list, int add_space)
{
	char	*str;

	if (buffer->pos == 0) // means we have "$ " -> no expand!
	{
		append_buffer(buffer, '$');
		if (push_buf_to_toklist(buffer, token_list, WORD) == FAIL)
			return (FAIL);
	}	
	append_buffer(buffer, '\0');
	str = getenv(buffer->buf);
	if (str == NULL)
		str = "";
	if (add_token_to_list(token_list, WORD, str) == FAIL)
		return (FAIL);
	free(buffer->buf);
	initialize_buffer(buffer);
	if (add_space) 
		append_buffer(buffer, ' ');
	return (SUCCESS);
}
