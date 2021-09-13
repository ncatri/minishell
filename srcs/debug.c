#include "debug.h"

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

	t = token->type;
	printf("type: %d, data: %s\n", token->type, token->data);
}
