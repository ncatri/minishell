#include "lexer.h"

t_error	f_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	(void)token_list;
	
	if (ft_isalnum(cursor))
	{
		append_buffer(buffer, cursor);
		*state = ST_IN_WORD;
	}
	return (SUCCESS);
}

t_error	f_inword(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	t_token *token;

	if (ft_isalnum(cursor))
		append_buffer(buffer, cursor);
	if (ft_isspace(cursor) || cursor == '\0')
	{
		append_buffer(buffer, '\0');
		token = new_token(WORD, buffer->buf);
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
		initialize_buffer(buffer);
		*state = ST_TRANSITION;
	}
	return (SUCCESS);
}
