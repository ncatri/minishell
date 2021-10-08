#include "execution.h"

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

int	execution()
{
	int			nb_cmds = 7;
	int 		nb_pipes = nb_cmds - 1;
	int 		pipesfd[nb_pipes][2];
	t_pid 		pids[7];
	pid_t		fork_res;
	int 		i;

	allpipes_action(pipesfd, nb_pipes, INITIALIZE);
	i = -1;
	while (++i < nb_cmds)
	{
		wait_previous_heredoc(commands[i].input, pids, i);
		fork_res = fork();
		if (fork_res == CHILD)
		{
			connect_input_pipe(i, commands[i].input, pipesfd);
			connect_output_pipe(i, nb_cmds, commands[i].output, pipesfd);
			input_redirection(commands[i].input);
			output_redirection(commands[i].output);
			allpipes_action(pipesfd, nb_pipes, DESTROY);
			execve(commands[i].exec, commands[i].args, NULL);
		}
		else
			fill_pids(fork_res, commands[i].input, pids, i);
	}
	allpipes_action(pipesfd, nb_pipes, DESTROY);
	wait_childs();
}