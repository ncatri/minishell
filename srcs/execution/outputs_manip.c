#include "execution.h"

int	output_redirection(char **outputs)
{
	int j;
	if (outputs != NULL)
	{
		j = -1;
		while (outputs[++j])
			dup2(open(outputs[j], O_RDWR | O_TRUNC | O_CREAT, 777), STDOUT_FILENO);	
	}
	return (0);
}

int	connect_output_pipe(int i, int nb_cmds, char **output, int pipesfd[][2])
{
	if (i < nb_cmds - 1 && output == NULL)
		dup2(pipesfd[i][WRITE], STDOUT_FILENO);
	return (0);
}