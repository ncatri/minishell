#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	allpipes_action(int pipesfd[][2], int nb_pipes, pipes action)
{
	int i;
	
	i = -1;
	if (action == DESTROY)
	{
		while (++i < nb_pipes)
		{
			if (close(pipesfd[i][READ]) == -1)
				return (1);
			if (close(pipesfd[i][WRITE]) == -1)
				return (1);
		}
	}
	else
	{
		while (++i < nb_pipes)
		{
			if (pipe(pipesfd[i]) == -1)
				return (-1);
		}
	}
	return (0);
}

int	my_execve(t_command *cmd, char **env)
{
	ft_pushfront_array((void ***)&cmd->args, cmd->executable, cmd->number_args);
	cmd->number_args++;
	ft_pushback_array((void ***)&cmd->args, NULL, cmd->number_args);
	cmd->executable = create_command_path(env, cmd->executable);
	execve(cmd->executable, cmd->args, NULL);
	return (0);
}

t_error	connections(int i, t_command *cmd, int pipesfd[][2])
{

	connect_input_pipe(i, cmd->input_redir, pipesfd);
	connect_output_pipe(i, cmd->output_redir, pipesfd);
	input_redirection(cmd->input_redir);
	output_redirection(cmd->output_redir);
	return (0);
}

t_error	execution(t_command **commands)
{
	int 		nb_pipes = g_global.num_cmds - 1;
	int 		pipesfd[nb_pipes][2];
	t_pid 		*pids;
	pid_t		fork_res;
	int 		i;

	pids = malloc(g_global.num_cmds * sizeof(t_pid));
	allpipes_action(pipesfd, nb_pipes, INITIALIZE);
	i = -1;
	if (g_global.num_cmds == 1 && !commands[0]->output_redir)
		if (check_builtin(commands[0]) == 1)
			return (0);
	while (++i < g_global.num_cmds)
	{
		wait_previous_heredoc(commands[i]->input_redir, pids, i);
		fork_res = fork();
		if (fork_res == CHILD)
		{
			connections(i, commands[i], pipesfd);
			allpipes_action(pipesfd, nb_pipes, DESTROY);
			if (is_builtin(commands[i]))
			{
				check_builtin(commands[i]);
				exit(1);
			}
			else
				my_execve(commands[i], g_global.envp);
		}
		else
			fill_pids(fork_res, commands[i]->input_redir, pids, i);
	}
	allpipes_action(pipesfd, nb_pipes, DESTROY);
	wait_childs();
	return (0);
}
