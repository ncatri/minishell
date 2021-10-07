#include "execution.h"

void	wait_childs()
{
	int status;
	pid_t wait_return;

	while ((wait_return = wait(&status)) > 0);
}

void	allpipes_action(int pipesfd[][2], int nb_pipes, pipes action)
{
	int i = -1;

	if (action == DESTROY)
	{
		while (++i < nb_pipes)
		{
			close(pipesfd[i][READ]);
			close(pipesfd[i][WRITE]);
		}
	}
	else
	{
		while (++i < nb_pipes)
			pipe(pipesfd[i]);
	}
}

void	fill_commands(t_cmd *commands, char **cmds, char *args[10][10], char *files[][20])
{
	int i;

	i = 0;
	while (cmds[i])
	{
		commands[i].exec = cmds[i];
		commands[i].args = args[i];
		i++;
	}
	commands[0].input = NULL;
	commands[0].output = NULL;
	commands[1].input = NULL;
	commands[1].output = NULL;
	commands[2].input = files[0];
	commands[2].output = files[1];
	commands[3].input = NULL;
	commands[3].output = NULL;
	commands[4].input = files[2];
	commands[4].output = NULL;
	commands[5].input = NULL;
	commands[5].output = NULL;
	commands[6].input = NULL;
	commands[6].output = NULL;
	
}

int main(int argc, char **argv)
{

	(void)argc, (void)argv;
	//numeric datas and pipes
	int			nb_cmds = 7;
	int 		nb_pipes = nb_cmds - 1;
	int 		pipesfd[nb_pipes][2];
	t_pid 		pids[7];
	pid_t		fork_res;
	int 		i;
	//struct cmd
	char 		*cmds[] = {"/bin/ls", "/usr/bin/grep", "/bin/cat", "/usr/bin/rev", "/bin/cat", "/usr/bin/grep", "/usr/bin/wc", NULL};
	char 		*args[][10] = {{"ls", NULL}, {"grep", "file", NULL}, {"cat", NULL}, {"rev", NULL}, {"cat", "-e", NULL}, {"grep", "i", NULL}, {"wc", "-c", NULL}, {NULL}};
	t_cmd commands[10];
	char 		*files[][20] = {{"input1.txt", "input2.txt",  "input3.txt", "heredoc", NULL}, {"output1.txt", NULL}, {"input4.txt", "heredoc", NULL}, {"output2.txt", "output3.txt", "output4.txt", NULL}, {NULL}};

	allpipes_action(pipesfd, nb_pipes, INITIALIZE);
	fill_commands(commands, cmds, args, files);
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
		{
			pids[i].pid = fork_res;
			if (i == 2 || i == 4)
				pids[i].heredoc = 1;
			else
				pids[i].heredoc = 0;
		}
	}
	allpipes_action(pipesfd, nb_pipes, DESTROY);
	wait_childs();
}
