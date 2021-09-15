#include "lexer.h"

/* input: the command line, a char *.
 * output: a list of tokens
*/

t_error	tokenizer(char *line)
{
	char	*cursor;
	t_list	*token_list;
	enum e_machine_states	state;
	t_buffer	buffer;
	int		i;

	state = ST_TRANSITION;
	token_list = NULL;
	initialize_buffer(&buffer);
	if (line == NULL || buffer.buf == NULL)
		return (FAIL);
	cursor = line;
	i = ft_strlen(line);
	while (i-- >= 0)
	{
		analyzer(*cursor, &state, &token_list, &buffer);
		// check machine state
		// depending on the input, update machine state
		// do something with the input
		cursor++;
	}
	// conclude following machine state
	printf("%s\n", line);
	print_token_list(token_list);	
	return (SUCCESS);
}

t_error	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	t_error	(*f[NUM_OF_STATES])(char cursor, \
			enum e_machine_states *state, t_list** token_list, t_buffer *buffer);
	t_error check;

	if (!state || !token_list || !buffer)
		return (FAIL);
	f[ST_TRANSITION] = f_transition;
	f[ST_IN_WORD] = f_inword;
	f[ST_OPEN_DQUOTE] = f_doublequote;
	f[ST_OPEN_SQUOTE] = f_singlequote;

	check = (*f[*state])(cursor, state, token_list, buffer);
	return (check);
}

t_error	initialize_buffer(t_buffer *buf)
{
	buf->buf = ft_calloc(sizeof(char), BUF_SIZE);
	buf->size = BUF_SIZE;
	buf->pos = 0;
	buf->n_squote = 0;
	buf->n_dquote = 0;
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
