#include "../includes/execution.h"

void first_child(int *ab)
{
	pid_t a;
	a = fork();
	if (a == 0)
	{
		close(ab[READ]);
		dup2(ab[WRITE], STDOUT_FILENO);
		//write from a to b
		printf("Hello world");
		close(ab[WRITE]);
		exit(1);
	}
}

void second_child(int *ab, int *bc)
{
	pid_t b;
	char *argv[] = {"ls", NULL};
	b = fork();
	if (b == 0)
	{
		close(bc[READ]);
		close(ab[WRITE]);
		//read from a
		dup2(ab[READ], STDIN_FILENO);
		//write from b to c
		dup2(bc[WRITE], STDOUT_FILENO);
		execve("/bin/ls", argv, NULL);
		exit(1);
	}
}

void third_child(int *bc)
{
	pid_t c;
	char *argv[] = {"wc", "-l", NULL};

	c = fork();
	if (c == 0)
	{
		close(bc[WRITE]);
		//read from b
		dup2(bc[READ], STDIN_FILENO);
		execve("/usr/bin/wc", argv, NULL);
		exit(1);
	}

}

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
	//(void)argc;
	//(void)argv;
	//char *line;

	//while (1)
	//{
	//	line = readline("minishell ===> ");
	//	tokenizer(line);
	//	free(line);
	//}
	//return (0);
	(void)argc, (void)argv;
	int nb_pipes = 1;
	int pipesfd[2][2];
	int status;
	int i = -1;
	pid_t wait_return;

	while (++i <= nb_pipes)
		pipe(pipesfd[i]);
	//create_all_childs(pipesfd, 3)
	first_child(pipesfd[READ]);
	second_child(pipesfd[READ], pipesfd[WRITE]);
	third_child(pipesfd[WRITE]);
	i = -1;
	while (++i <= nb_pipes)
	{
		close(pipesfd[i][READ]);
		close(pipesfd[i][WRITE]);
	}
	while ((wait_return = wait(&status)) > 0)
		;
}
