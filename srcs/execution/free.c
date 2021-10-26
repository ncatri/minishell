#include "execution.h"

void	free_splits(char **chain, int i)
{
	while (--i >= 0)
		free(chain[i]);
	free(chain);
}

int	number_of_split(char **splitresult)
{
	int	i;

	i = 0;
	if (!splitresult)
		return (0);
	while (splitresult[i])
		i++;
	return (i);
}

void	free_loop(char *line, t_command **cmd_array)
{
	int i;

	i = 0;
	free(line);
	while (i < g_global.num_cmds)
	{
		ft_lstclear(&cmd_array[i]->input_redir, free);
		ft_lstclear(&cmd_array[i]->output_redir, free);
		free(cmd_array[i]->args);
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

int	return_message(char *message, int return_status)
{
	if (message != NULL)
		printf("%s", message);
	return (return_status);
}