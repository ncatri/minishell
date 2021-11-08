#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_bool is_executable(char *cmd_exec)
{
	struct stat file;

	if (stat(cmd_exec, &file) == 0 && file.st_mode & S_IXUSR)
		return (TRUE);
	return (FALSE);
}

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

void	verif_exec(t_command *cmd, char **env)
{

