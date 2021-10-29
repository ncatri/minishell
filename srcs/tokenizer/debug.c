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
	if (t == WORD || t == WORD_NOEXPAND || t == WORD_EXPANDED)
	{
		if (t == WORD)
			str = "WORD";
		else if (t == WORD_NOEXPAND)
			str = "WORD_NOEXPAND";
		else if (t == WORD_EXPANDED)
			str = "WORD_EXPANDED";
		printf("%s |%s|", str, token->data);
		if (token->concat_next)
			printf(" [linked]");
		printf("\n");
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
