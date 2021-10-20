#include "execution.h"

t_error	browse_inputs(t_list *input_list)
{
	int 	fd;
	t_list *cursor;
	t_redir_in *input;

	cursor = input_list;
	while (cursor)
	{
		input = cursor->content;
		if (input->type == HERE_DOC)
		{
			fd = heredoc(input->name_delim, fd);
			if (fd == -1)
				return (-1);
			if (cursor->next == NULL)
				dup2(fd, STDIN_FILENO);
		}
		else
		{
			if (open(input->name_delim, O_RDWR, 777) == -1)
				return (-1);
			if (cursor->next == NULL)
				dup2(open(input->name_delim, O_RDWR, 777) , STDIN_FILENO);
		}
		cursor = cursor->next;
	}
	return (0);
}

t_error	connect_input_pipe(int i, t_list *input, int pipesfd[][2])
{
//	printf("in connect_input_pipe, pid %d, parent %d\n", getpid(), getppid());
	if (i != 0 && input == NULL)
		dup2(pipesfd[i - 1][READ] , STDIN_FILENO);
	return (0);
}

t_error	input_redirection(t_list *input_list)
{
	if (input_list != NULL)
		browse_inputs(input_list);
	return (0);
}
