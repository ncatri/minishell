#include "execution.h"
#include "minishell.h"
#include "parser.h"

void	final_exec(t_command **commands, int i)
{
	if (is_builtin(commands[i]))
	{
		if (check_builtin(commands[i]))
			exit(0);
		else
			exit (1);
	}
	else
	{
		execve(commands[i]->executable, commands[i]->args, g_global.envp);
		exit(1);
	}
}
