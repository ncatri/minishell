#include "execution.h"

int	find_previous_hd(t_pid *pid, int i)
{
	i--;
	while (i >= 0)
	{
		if (pid[i].heredoc == 1)
			return (i);
		i--;
	}
	return(-1);
}

int	is_heredoc(char **input)
{
	int i = 0;

	if (input == NULL)
		return (-1);
	while (input[i])
	{
		if (ft_strncmp(input[i], "heredoc", 7) == 0)
			return (1);
		i++;
	}
	return (-1);
}

int	wait_previous_heredoc(char **input, t_pid *pids, int i)
{
	int previous_hd;

	if (is_heredoc(input))
	{
		previous_hd = find_previous_hd(pids, i);
		if (previous_hd != -1)
			waitpid(pids[previous_hd].pid, 0, 0);
	}
	return (0);
}

int	heredoc(char *terminator, int fd)
{
	char *line;

	line = NULL;
	fd = open("heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (get_next_line(READ, &line) != 0 && ft_strncmp(line, terminator, ft_strlen(terminator)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	fd = open("heredoc.txt", O_RDWR, 0777);
	return (fd);
}