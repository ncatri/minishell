#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	char	*line;
	t_list	*token_list;
	t_command	**cmd_array;

	g_global.envp = copy_env(envp);
	if (argc != 1)
		return (printf("\x1B[31mToo much args\n\033[0m"));
	while (1)
	{
		setup_main_signals();
		line = readline("\033[0;32mminishell ===> \033[0m");
		if (line == NULL)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		token_list = tokenizer(line);
		expand_variables(token_list);
	//	print_token_list(token_list);
		cmd_array = parser(token_list);
	//	print_command_array(cmd_array, g_global.num_cmds);
		if (cmd_array)
			execution(cmd_array);
		ft_lstclear(&token_list, free_token);
		//print_token_list(token_list);
		//print_command_array(cmd_array, g_global.num_cmds);
		
		//ft_lstclear(&token_list, free_token); --> crash with [ls | rev | rev | cat -e]
		free_loop(line, cmd_array);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
	}
	free_splits(g_global.envp, number_of_split(g_global.envp));
	return (0);
}
