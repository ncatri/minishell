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
	char *argv[] = {"grep", "mini", NULL};

	c = fork();
	if (c == 0)
	{
		close(bc[WRITE]);
		//read from b
		dup2(bc[READ], STDIN_FILENO);
		execve("/usr/bin/grep", argv, NULL);
		exit(1);
	}

}

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
	int ab[2], bc[2];
	pid_t wait_return;
	int status;

	pipe(ab);
	pipe(bc);
	first_child(ab);
	second_child(ab, bc);
	third_child(bc);
	close(ab[WRITE]);
	close(ab[READ]);
	close(bc[WRITE]);
	close(bc[READ]);
	while ((wait_return = wait(&status)) > 0)
		;
}
