#include "../includes/execution.h"

//void first_child(int *ab)
//{
//	pid_t a;
//	a = fork();
//	if (a == 0)
//	{
//		close(ab[READ]);
//		dup2(ab[WRITE], STDOUT_FILENO);
//		//write from a to b
//		printf("Hello world");
//		close(ab[WRITE]);
//		exit(1);
//	}
//}

//void second_child(int *ab, int *bc)
//{
//	pid_t b;
//	char *argv[] = {"ls", NULL};
//	b = fork();
//	if (b == 0)
//	{
//		close(bc[READ]);
//		close(ab[WRITE]);
//		//read from a
//		dup2(ab[READ], STDIN_FILENO);
//		//write from b to c
//		dup2(bc[WRITE], STDOUT_FILENO);
//		execve("/bin/ls", argv, NULL);
//		exit(1);
//	}
//}

//void third_child(int *bc)
//{
//	pid_t c;
//	char *argv[] = {"wc", "-l", NULL};

//	c = fork();
//	if (c == 0)
//	{
//		close(bc[WRITE]);
//		//read from b
//		dup2(bc[READ], STDIN_FILENO);
//		execve("/usr/bin/wc", argv, NULL);
//		exit(1);
//	}

//}

//void	create_all_childs(int **pipesfd, int nb_childs)
//{
//	int i;
//	pid_t pid;

//	i = -1;
//	while (++i < nb_childs)
//	{
//		pid = fork();
//		if (pid == 0)
//		{
//			//child
//		}
//		else
//		{
//			//dad
//		}
//	}
//}

int main(int argc, char **argv)
{
	//variables
	(void)argc, (void)argv;
	int	nb_cmds = 3;
	char *cmds[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/wc", NULL};
	char *first_args[] = {"ls", NULL};
	char *scnd_args[] = {"grep", "e", NULL};
	char *thrd_args[] = {"wc", NULL};
	char **args[4];
	args[0] = first_args;
	args[1] = scnd_args;
	args[2] = thrd_args;
	args[3] = NULL;
	int pipes_idmax = 1;
	int pipesfd[pipes_idmax + 1][2];
	int pipe_count = 0;

	//create pipes
	int i;
	i = -1;
	while (++i <= pipes_idmax)
		pipe(pipesfd[i]);
	//forks and processes
	i = -1;
	while (++i < nb_cmds)
	{
		if (fork() == 0)
		{
			if (i != 0)
			{
				//input = cmd d'avant;
				if (i == 2)
					pipe_count++;
				dup2(pipesfd[pipe_count][READ] , STDIN_FILENO);
				pipe_count++;
			}
			if (i < 2)
			{
				//output = cmd d'apres;
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
