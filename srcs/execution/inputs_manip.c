#include "execution.h"

int	browse_inputs(char **input_cmd)
{
	int j;
	int fd;

	j = -1;
	while (input_cmd[++j])
	{
		if (ft_strncmp(input_cmd[j], "heredoc", 7) == 0)
		{
			fd = heredoc("eof", fd);
			if (fd == -1)
				return (-1);
			if (input_cmd[j + 1] == NULL)
				dup2(fd, STDIN_FILENO);
		}
		else
		{
			if (open(input_cmd[j], O_RDWR, 777) == -1)
				return (-1);
		}
	}
	return (j);
}

int	connect_input_pipe(int i, char **input, int pipesfd[][2])
{
	if (i != 0 && input == NULL)
		dup2(pipesfd[i - 1][READ] , STDIN_FILENO);
	return (0);
}

int	input_redirection(char **input)
{
	int j;

	if (input != NULL)
	{
		j = browse_inputs(input);
		if (ft_strncmp(input[j - 1], "heredoc", 7) != 0)
			dup2(open(input[j - 1], O_RDWR, 777) , STDIN_FILENO);
	}
	return (0);
}