#include "lexer.h"

void	print_token_list(t_list *token_list)
{
	t_list	*cursor;
	int		counter;

	counter = 1;
	cursor = token_list;
	while (cursor)
	{
		printf("--- token %d ---\n", counter++);
		print_token((t_token*)(cursor->content));
		cursor = cursor->next;
	}
}


void	print_token(t_token *token)
{
	int t;
	char	*str;

	str = NULL;
	t = token->type;
	if (t == WORD)
	{
		str = "WORD";
		printf("%s, data: %s, link to next: %d\n", str, token->data, token->concat_next);
	}
	else
	{
		if (t == LESS)
			str = "LESS";
		else if (t == DLESS)
			str = "DLESS";
		else if (t == GREAT)
			str = "GREAT";
		else if (t == DGREAT)
			str = "DGREAT";
		else if (t == PIPE)
			str = "PIPE";
		printf("%s\n", str);
	}
}
