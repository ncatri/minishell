#include "lexer.h"

/* input: the command line, a char *.
 * output: a list of tokens
*/

int	tokenizer(char *line)
{
	char	*cursor;
	t_list	*token_list;
	enum e_machine_states	state;
	t_buffer	buffer;
	int		i;

	state = ST_START;
	token_list = NULL;
	initialize_buffer(&buffer);
	if (line == NULL || buffer.buf == NULL)
		return (-1);
	cursor = line;
	i = ft_strlen(line);
	while (i-- >= 0)
	{
		printf("cursor: %c\n", *cursor);
		analyzer(*cursor, &state, &token_list, &buffer);
		// check machine state
		// depending on the input, update machine state
		// do something with the input
		cursor++;
	}
	// conclude following machine state
	printf("%s\n", line);
	print_token_list(token_list);	
		
	return (0);
}

void	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer)
{
	t_token	*token;

	if (!state || !token_list || !buffer)
		return;
	if (ft_isalnum(cursor) && (*state == ST_START || *state == ST_IN_WORD))
	{
		append_buffer(buffer, cursor);
		*state = ST_IN_WORD;
	}
	else if ((ft_isspace(cursor) || cursor == '\0') && *state == ST_IN_WORD)
	{
		append_buffer(buffer, '\0');
		token = new_token(WORD, buffer->buf);
		if (!token)
			return;
		ft_lstadd_back(token_list, ft_lstnew(token));
		initialize_buffer(buffer);
		*state = ST_START;
	}
	else
		return ;

}

t_bool	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}


void	initialize_buffer(t_buffer *buf)
{
	// need to return a t_err
	buf->buf = ft_calloc(sizeof(char), BUF_SIZE);
	buf->size = BUF_SIZE;
	buf->pos = 0;
}

void	append_buffer(t_buffer *buffer, char c)
{
	char	*tmp;

	if (buffer->pos >= buffer->size)
	{
		tmp = malloc(sizeof(char) * (buffer->size + BUF_SIZE));
		if (!tmp)
		{
			free(buffer->buf);
			return;
		}
		ft_memcpy(tmp, buffer->buf, buffer->size);
		buffer->size += BUF_SIZE;
		free(buffer->buf);
		buffer->buf = tmp;
	}
	buffer->buf[buffer->pos] = c;
	buffer->pos++;
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
