#include "parser.h"

void	parser(t_list *token_list)
{
	int					cmd_count;
	t_simple_command	*commands;

	print_token_list(token_list);
	cmd_count = count_pipes(token_list) + 1;
	printf("cmd_count: %d\n", cmd_count);
	commands = malloc(sizeof(t_simple_command) * cmd_count);

}

int	count_pipes(t_list *token_list)
{
	t_token	*tok;
	t_list	*cursor;
	int		count;

	count = 0;
	cursor = token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->type == PIPE)
			count++;
		cursor = cursor->next;
	}
	return (count);
}
