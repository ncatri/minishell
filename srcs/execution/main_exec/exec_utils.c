#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	allpipes_action(int **pipesfd, int nb_pipes, t_pipes action)
{
	int	i;

	i = -1;
	if (action == DESTROY)
	{
		while (++i < nb_pipes)
		{
			if (close(pipesfd[i][READ]) == -1)
				return (FAIL);
			if (close(pipesfd[i][WRITE]) == -1)
				return (FAIL);
		}
	}
	else
	{
		while (++i < nb_pipes)
		{
			if (pipe(pipesfd[i]) == -1)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	build_exec(t_command *cmd, char **env)
{
	ft_pushfront_array((void ***)&cmd->args, cmd->executable, cmd->number_args);
	cmd->number_args++;
	ft_pushback_array((void ***)&cmd->args, NULL, cmd->number_args);
	if (open(cmd->executable, O_RDONLY) == -1)
		cmd->executable = create_command_path(env, cmd->executable);
	if (open(cmd->executable, O_DIRECTORY) >= 0)
		cmd->executable = NULL;
	if (cmd->executable == NULL)
	{
		if (cmd->input_redir != NULL)
			exit (SUCCESS);
		g_global.ret = 127;
		ft_putstr_fd("\x1B[31mCommand not found\n\033[0m", 2);
		exit(g_global.ret);
	}
	return (SUCCESS);
}

t_error	connections(int i, t_command *cmd, int **pipesfd)
{
	if (connect_input_pipe(i, cmd->input_redir, pipesfd) == FAIL)
		return (FAIL);
	if (connect_output_pipe(i, cmd->output_redir, pipesfd) == FAIL)
		return (FAIL);
	if (input_redirection(cmd->input_redir) == FAIL)
		return (FAIL);
	if (output_redirection(cmd->output_redir) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	child_stuff(int i, t_command **commands, int nb_pipes, int **pipesfd)
{
	signal(SIGINT, SIG_DFL);
	if (is_heredoc(commands[i]->input_redir) == 1)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
	if (connections(i, commands[i], pipesfd) == FAIL)
	{
		g_global.ret = 1;
		exit (g_global.ret);
	}
	if (!is_builtin(commands[i]))
		build_exec(commands[i], g_global.envp);
	if (allpipes_action(pipesfd, nb_pipes, DESTROY) == FAIL)
		return (FAIL);
	if (is_builtin(commands[i]))
	{
		check_builtin(commands[i]);
		exit(1);
	}
	else
	{
		execve(commands[i]->executable, commands[i]->args, g_global.envp);
		exit(34);
	}
	return (SUCCESS);
}