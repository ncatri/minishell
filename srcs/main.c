#include "../includes/execution.h"

int main(int argc, char **argv)
{
	(void)argc, (void)argv;
	//commands and args
	char *cmds[] = {"/bin/ls", "/usr/bin/grep", "/bin/cat", "/usr/bin/rev", "/bin/cat", "/usr/bin/grep", "/usr/bin/wc", NULL};
	char *first_args[] = {"ls", NULL};
	char *scnd_args[] = {"grep", "e", NULL};
	char *thrd_args[] = {"cat", NULL};
	char *fourth_args[] = {"rev", NULL};
	char *fifth_args[] = {"cat", "-e", NULL};
	char *sixth_args[] = {"grep", "i", NULL};
	char *seventh_args[] = {"wc", "-c", NULL};
	char **args[8];
	args[0] = first_args;
	args[1] = scnd_args;
	args[2] = thrd_args;
	args[3] = fourth_args;
	args[4] = fifth_args;
	args[5] = sixth_args;
	args[6] = seventh_args;
	args[7] = NULL;
	//numeric datas and pipes
	int	nb_cmds = 7;
	int pipes_idmax = 5;
	int pipesfd[pipes_idmax + 1][2];
	int pipe_count;

	//create pipes
	int i;
	i = -1;
	while (++i <= pipes_idmax)
		pipe(pipesfd[i]);
	//forks and processes
	i = -1;
	while (++i < nb_cmds)
	{
		pipe_count = i;
		if (fork() == 0)
		{
			if (i != 0)
			{
				//Not the first cmd -> input = previous pipe;
				dup2(pipesfd[pipe_count - 1][READ] , STDIN_FILENO);
			}
			if (i < nb_cmds - 1)
			{
				//not the last cmd (i starts at 0 so if i = 6 we are at the 7th cmd) -> output = next pipe;
				dup2(pipesfd[pipe_count][WRITE], STDOUT_FILENO);
			}
			//close
			int j = -1;
			while (++j <= pipes_idmax)
			{
				close(pipesfd[j][READ]);
				close(pipesfd[j][WRITE]);
			}
			execve(cmds[i], args[i], NULL);
		}
		else
		{
			//dad
		}
	}
	//closing pipes
	i = -1;
	while (++i <= pipes_idmax)
	{
		close(pipesfd[i][READ]);
		close(pipesfd[i][WRITE]);
	}
	//waiting chidls
	int status;
	pid_t wait_return;
	while ((wait_return = wait(&status)) > 0);
}
