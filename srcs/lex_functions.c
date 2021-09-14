#include "lexer.h"

t_error	f_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	(void)token_list;
	
	if (ft_isalnum(cursor))
	{
		append_buffer(buffer, cursor);
		*state = ST_IN_WORD;
	}
	else if (cursor == '"')
	{
		*state = ST_OPEN_DQUOTE;
		buffer->n_dquote++;
	}
	else if (cursor == '\'')
	{
		*state = ST_OPEN_SQUOTE;
		buffer->n_squote++;
	}
	return (SUCCESS);
}

t_error	f_inword(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	t_token *token;

	if (ft_isalnum(cursor))
		append_buffer(buffer, cursor);
	else if (ft_isspace(cursor) || cursor == '\0')
	{
		append_buffer(buffer, '\0');
		token = new_token(WORD, buffer->buf);
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
		initialize_buffer(buffer);
		*state = ST_TRANSITION;
	}
	else if (cursor == '"')
	{
		*state = ST_OPEN_DQUOTE;
		buffer->n_dquote++;
	}
	else if (cursor == '\'')
	{
		*state = ST_OPEN_SQUOTE;
		buffer->n_squote++;
	}
	return (SUCCESS);
}

t_error	f_doublequote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	(void)token_list;

	if (ft_isalnum(cursor) || ft_isspace(cursor) ||\
			ft_is_incharset(cursor, "<>.,?/\\()"))
		append_buffer(buffer, cursor);
	else if (cursor == '"')
	{
		buffer->n_dquote--;
		if (buffer->n_dquote == 0)
			*state = ST_IN_WORD;
	}
	else if (cursor == '\'')
	{
		buffer->n_squote++;
		*state = ST_OPEN_SQUOTE;
	}
	else if (cursor == '\0')
		printf("Error: unclosed double quote\n");
	else
		printf("non covered case in f_doublequote\n");
	return (SUCCESS);
}
