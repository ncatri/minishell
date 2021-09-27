#include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_list	*token_list;

	while (1)
	{
		line = readline("minishell ===> ");
		token_list = tokenizer(line);
		parser(token_list);
		ft_lstclear(&token_list, free_token);
		free(line);
	}
	return (0);
}
