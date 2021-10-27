#include "execution.h"

t_error	browse_inputs(t_list *input_list)
{
	int			fd;
	t_list		*cursor;
	t_redir_in	*input;

	cursor = input_list;
	while (cursor)
	{
		input = cursor->content;
		if (input->type == HERE_DOC)
		{
			fd = heredoc(input->name_delim, fd);
			if (fd == FAIL)
				return (FAIL);
			if (cursor->next == NULL)
				dup2(fd, STDIN_FILENO);
			unlink("heredoc.txt");
		}
		else
		{
			if (open(input->name_delim, O_RDONLY) == -1)
				return (ret_msg("Input file does not exist\n", FAIL));
			if (cursor->next == NULL)
				dup2(open(input->name_delim, O_RDONLY), STDIN_FILENO);
		}
		cursor = cursor->next;
	}
	return (SUCCESS);
}

t_error	connect_input_pipe(int i, t_list *input, int pipesfd[][2])
{
	int	ret;

	ret = 0;
	if (i != 0 && input == NULL)
		ret = dup2(pipesfd[i - 1][READ], STDIN_FILENO);
	if (ret == -1)
		return (FAIL);
	return (SUCCESS);
}

t_error	input_redirection(t_list *input_list)
{
	if (input_list != NULL)
		if (browse_inputs(input_list) == FAIL)
			return (FAIL);
	return (SUCCESS);
}
