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
	if (cmd->executable == NULL)
		exit (printf("Bad command\n"));
	return (SUCCESS);
}

t_error	connections(int i, t_command *cmd, int pipesfd[][2])
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

int	child_stuff(int i, t_command **commands, int nb_pipes, int pipesfd[][2])
{
	build_exec(commands[i], g_global.envp);
	if (connections(i, commands[i], pipesfd) == FAIL)
		return (FAIL);
	if (allpipes_action(pipesfd, nb_pipes, DESTROY) == FAIL)
		return (FAIL);
	if (is_builtin(commands[i]))
	{
		check_builtin(commands[i]);
		exit(1);
	}
	else
		execve(commands[i]->executable, commands[i]->args, NULL);
	return (SUCCESS);
}

t_error	execution(t_command **commands)
{
	int 		nb_pipes = g_global.num_cmds - 1;
	int 		pipesfd[nb_pipes][2];
	t_pid 		*pids;
	pid_t		fork_res;
	int 		i;

	pids = malloc(g_global.num_cmds * sizeof(pid_t));
	if (pids == NULL)
		return (FAIL);
	if (allpipes_action(pipesfd, nb_pipes, INITIALIZE) == FAIL)
		return (FAIL);
	i = -1;
	if (g_global.num_cmds == 1 && !commands[0]->output_redir)
		if (check_builtin(commands[0]) == 1)
			return (SUCCESS);
	while (++i < g_global.num_cmds)
	{
		wait_previous_heredoc(commands[i]->input_redir, pids, i);
		fork_res = fork();
		if (fork_res == CHILD)
			child_stuff(i, commands, nb_pipes, pipesfd);
		else if (fork_res > 0)
			fill_pids(fork_res, commands[i]->input_redir, pids, i);
		else
			return (FAIL);
	}
	if (allpipes_action(pipesfd, nb_pipes, DESTROY) == FAIL)
		return (FAIL);
	wait_childs();
	return (SUCCESS);
}
