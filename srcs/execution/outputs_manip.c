#include "execution.h"

t_error	output_redirection(t_list *output_list)
{
	t_list *cursor;
	t_redir_out *output;

	cursor = output_list;
	while (cursor)
	{
		output = cursor->content;
		dup2(open(output->filename, O_RDWR | O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);	
		cursor = cursor->next;
	}
	return (0);
}

t_error	connect_output_pipe(int i, t_list *output_list, int pipesfd[][2])
{
	if (i < g_global.num_cmds - 1 && output_list == NULL)
		dup2(pipesfd[i][WRITE], STDOUT_FILENO);
	return (0);
}
