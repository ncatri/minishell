#include "execution.h"

static int	heredoc_type(t_redir_in *input, t_list *cursor)
{
	int	fd;

	fd = 0;
	fd = heredoc(input->name_delim, fd);
	if (fd == FAIL)
		return (FAIL);
	if (cursor->next == NULL)
		dup2(fd, STDIN_FILENO);
	unlink("heredoc.txt");
	return (SUCCESS);
}

t_error	browse_inputs(t_list *input_list)
{
	t_list		*cursor;
	t_redir_in	*input;

	cursor = input_list;
	while (cursor)
	{
		input = cursor->content;
		if (input->type == HERE_DOC)
		{
			if (heredoc_type(input, cursor) == FAIL)
				return (FAIL);
		}
		else
		{
			if (open(input->name_delim, O_RDONLY, 0644) == -1)
				return (ret_msg("Input file does not exist\n", FAIL));
			if (cursor->next == NULL)
				dup2(open(input->name_delim, O_RDONLY, 0644), STDIN_FILENO);
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
