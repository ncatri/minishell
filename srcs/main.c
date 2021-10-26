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

	g_global.envp = envp;
	if (argc != 1)
		return (printf("\x1B[31mToo much args\n\033[0m"));
	while (1)
	{
		setup_main_signals();
		line = readline("\033[0;32m minishell ===> \033[0m");
		if (line == NULL)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		token_list = tokenizer(line);
//		expand_variables(token_list);
		print_token_list(token_list);
		cmd_array = parser(token_list);
	//	print_command_array(cmd_array, g_global.num_cmds);
//		if (cmd_array)
//			execution(cmd_array);
		
		ft_lstclear(&token_list, free_token);
		//print_token_list(token_list);
		//print_command_array(cmd_array, g_global.num_cmds);
		
		//ft_lstclear(&token_list, free_token); --> crash with [ls | rev | rev | cat -e]
		free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
	}
	return (0);
}
