#include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *line;

	while (1)
	{
		line = readline("minishell ===> ");
		tokenizer(line);
		free(line);
	}
	return (0);
}
