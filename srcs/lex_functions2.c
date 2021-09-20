#include "lexer.h"

t_error	f_less(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	t_token	*token;

	if (ft_isalnum(cursor) || ft_isspace(cursor) || cursor == '\0')
	{
		token = new_token(LESS, "");
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
		if (ft_isalnum(cursor))
			append_buffer(buffer, cursor); // need to save the character
		*state = ST_IN_WORD;
	}
	else if (cursor == '<')
	{
		token = new_token(DLESS, "");
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
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
	t_token	*token;

	if (ft_isalnum(cursor) || ft_isspace(cursor) || cursor == '\0')
	{
		token = new_token(GREAT, "");
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
		if (ft_isalnum(cursor))
			append_buffer(buffer, cursor); // need to save the character
		*state = ST_IN_WORD;
	}
	else if (cursor == '>')
	{
		token = new_token(DGREAT, "");
		if (!token)
			return (FAIL);
		ft_lstadd_back(token_list, ft_lstnew(token));
		*state = ST_TRANSITION;
	}
	else if (cursor == '<')
		printf("syntax error\n");
	else
		printf("non covered case in f_less\n");
	return (SUCCESS);
}
