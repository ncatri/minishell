#include "parser.h"

t_error	push_command_to_array(t_command ***cmd_array, t_command *cmd_to_build)
{
	t_command	*cmd_ptr;

	cmd_ptr = malloc(sizeof(t_command));
	if (!cmd_ptr)
		return (FAIL);
	ft_memcpy(cmd_ptr, cmd_to_build, sizeof(t_command));
	if (pushback_array(cmd_array, cmd_ptr) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_error	pushback_array(t_command ***cmd_array, t_command *cmd_ptr)
{
	t_command	**new_array;

	new_array = malloc(sizeof(t_command*) * (g_global.num_cmds + 1));
	if (!new_array)
		return (FAIL);
	ft_memcpy(new_array, *cmd_array, sizeof(t_command*) * g_global.num_cmds);
	new_array[g_global.num_cmds] = cmd_ptr;
	free(*cmd_array);
	*cmd_array = new_array;
	return (SUCCESS);
}

void	free_array(void **ptr_array, int array_size)
{
	while (array_size-- > 0)
		free(ptr_array[array_size]);
	free(ptr_array);
}
