#include "execution.h"
#include "minishell.h"
#include "parser.h"

int **create_pipesfd(int nb_pipes)
{
	int **pipesfd;
	int i;

	pipesfd = malloc(sizeof(int *) * nb_pipes);
	if (pipesfd == NULL)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipesfd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (pipesfd);
}

t_error	execution(t_command **commands)
{
	int		nb_pipes;
	int		**pipesfd;
	t_pid	*pids;
	pid_t	fork_res;
	int		i;

	nb_pipes = g_global.num_cmds - 1;
	pipesfd = create_pipesfd(nb_pipes);
	pids = malloc(g_global.num_cmds * sizeof(t_pid));
	if (pids == NULL)
		return (FAIL);
	if (allpipes_action(pipesfd, nb_pipes, INITIALIZE) == FAIL)
		return (FAIL);
	if (g_global.num_cmds == 1 && !commands[0]->output_redir)
	{
		if (check_builtin(commands[0]) == 1)
		{
			free(pids);
			return (SUCCESS);
		}
	}
	i = -1;
	while (++i < g_global.num_cmds)
	{
		wait_previous_heredoc(commands[i]->input_redir, pids, i);
		if (is_heredoc(commands[i]->input_redir) == 1)
			g_global.heredoc = TRUE;
		fork_res = fork();
		g_global.pid = fork_res;
		tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
		if (fork_res == CHILD)
			child_stuff(i, commands, nb_pipes, pipesfd);
		else if (fork_res > 0)
			fill_pids(fork_res, commands[i]->input_redir, pids, i);
		else
			return (FAIL);
	}
	if (allpipes_action(pipesfd, nb_pipes, DESTROY) == FAIL)
		return (FAIL);
	free(pids);
	wait_childs();
	return (SUCCESS);
}
