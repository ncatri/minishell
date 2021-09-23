#include "lexer.h"

t_token *new_token(enum e_token_types type, char *buf)
{
	t_token *token;

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
	t_token *tok;

	tok = (t_token*)token;
	free(tok->data);
	free(tok);
}

t_error	add_token_to_list(t_list **token_list, int token_type, char *data)
{
	t_token *token;
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
