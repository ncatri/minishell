#include "execution.h"

void	wait_childs()
{
	int status;
	pid_t wait_return;

	while ((wait_return = wait(&status)) > 0);
}

int	fill_pids(int fork_res, char **input, t_pid *pids, int i)
{
	pids[i].pid = fork_res;
	if (is_heredoc(input) == 1)
		pids[i].heredoc = 1;
	else
		pids[i].heredoc = 0;
	return (0);
}