#include "execution.h"

t_error	output_redirection(t_list *output_list)
{
	t_list		*cursor;
	t_redir_out	*output;
	int			fd;

	cursor = output_list;
	while (cursor)
	{
		output = cursor->content;
		if (output->mode == APPEND)
			fd = open(output->filename, O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			fd = open(output->filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (FAIL);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (FAIL);
		cursor = cursor->next;
	}
	return (SUCCESS);
}

t_error	connect_output_pipe(int i, t_list *output_list, int pipesfd[][2])
{
	int	ret;

	ret = 0;
	if (i < g_global.num_cmds - 1 && output_list == NULL)
		ret = dup2(pipesfd[i][WRITE], STDOUT_FILENO);
	if (ret == -1)
		return (FAIL);
	return (SUCCESS);
}
