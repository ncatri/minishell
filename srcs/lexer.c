#include "lexer.h"

/* input: the command line, a char *.
 * output: a list of tokens
*/

int	tokenizer(char *line)
{
	char	*cursor;
	t_list	*token_list;
	enum e_machine_states	state;
	t_token	token;

	state = ST_START;
	if (line == NULL)
		return (NULL);
	cursor = line;
	while (cursor)
	{
		token.data = "";
		analyzer(cursor, &state, &token_list, &token);
		// check machine state
		// depending on the input, update machine state
		// do something with the input
	}
	// conclude following machine state
	printf("%s\n", line);
	return (0);
}

void	analyzer(char *cursor, enum e_machine_states *state, \
		t_list **token_list, t_token *token)
{
	char	one_char[2];

	if (!cursor || !state || !token_list || !token)
		return;
	ft_bzero(one_char, 2);
	one_char[0] = *cursor;
	if (ft_isalnum(*cursor))
			
}
