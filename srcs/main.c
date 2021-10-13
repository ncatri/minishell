#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	char	*line;
	t_list	*token_list;
	t_command	**cmd_array;

	if (argc != 1)
		return (printf("\x1B[31mToo much args\n\033[0m"));
	setup_signals();
	while (1)
	{
		line = readline("\033[0;32m minishell ===> \033[0m");
		if (line != NULL)
			add_history(line);
		token_list = tokenizer(line);
		expand_variables(token_list);
		print_token_list(token_list);
		cmd_array = parser(token_list);
		print_command_array(cmd_array, g_global.num_cmds);
		execution(cmd_array, env);
		
		ft_lstclear(&token_list, free_token);
		//print_token_list(token_list);
		//print_command_array(cmd_array, g_global.num_cmds);
		
		//ft_lstclear(&token_list, free_token); --> crash with [ls | rev | rev | cat -e]
		free(line);
	}
	return (0);
}
