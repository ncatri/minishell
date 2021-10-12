#include "execution.h"
#include "minishell.h"
#include "parser.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_list	*token_list;
	t_command	**cmd_array;

	while (1)
	{
		line = readline("\033[0;32mminishell ===> \033[0m");
		if (line != NULL)
			add_history(line);
		token_list = tokenizer(line);
		//print_token_list(token_list);
		cmd_array = parser(token_list);
		//print_command_array(cmd_array, g_global.num_cmds);
		execution(cmd_array, env);
		
		//printf("last elt of path: %s\n", last_elt_of_path(cmd_array[0]->executable));
		//ft_lstclear(&token_list, free_token); --> crash with [ls | rev | rev | cat -e]
		free(line);
	}
	return (0);
}
