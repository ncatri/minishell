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

t_error	push_buf_to_toklist(t_buffer *buffer, t_list **token_list, enum e_token_types tok_type)
{
	append_buffer(buffer, '\0');
	if (add_token_to_list(token_list, tok_type, buffer->buf) == FAIL)
		return (FAIL);
	free(buffer->buf);
	initialize_buffer(buffer);
	return (SUCCESS);
}

t_error	syntax_error(char c)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	write(2, &c, 1);
	write(2, "\n", 1);
	return (FAIL);
}

t_error	error_message(char* message)
{
	ft_putstr_fd(message, 2);
	return (FAIL);
}
