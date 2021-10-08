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

int	execution(t_command **commands)
{
	int 		nb_pipes = g_global.num_cmds - 1;
	int 		pipesfd[nb_pipes][2];
	t_pid 		*pids;
	pid_t		fork_res;
	int 		i;

	pids = malloc(g_global.num_cmds * sizeof(pid_t));
	allpipes_action(pipesfd, nb_pipes, INITIALIZE);
	i = -1;
	while (++i < g_global.num_cmds)
	{
		wait_previous_heredoc(commands[i]->input_redir, pids, i);
		fork_res = fork();
		if (fork_res == CHILD)
		{
			print_command(commands[i]);
			connect_input_pipe(i, commands[i]->input_redir, pipesfd);
			connect_output_pipe(i, commands[i]->output_redir, pipesfd);
			input_redirection(commands[i]->input_redir);
			output_redirection(commands[i]->output_redir);
			allpipes_action(pipesfd, nb_pipes, DESTROY);
			execve(commands[i]->executable, commands[i]->args, NULL);
		}
		else
			fill_pids(fork_res, commands[i]->input_redir, pids, i);
	}
	allpipes_action(pipesfd, nb_pipes, DESTROY);
	wait_childs();
	return (0);
}