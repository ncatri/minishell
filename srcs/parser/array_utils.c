#include "parser.h"

t_error	push_command_to_array(t_command ***cmd_array, t_command *cmd_to_build)
{
	t_command	*cmd_ptr;

	cmd_ptr = malloc(sizeof(t_command));
	if (!cmd_ptr)
		return (FAIL);
	ft_memcpy(cmd_ptr, cmd_to_build, sizeof(t_command));
	if (pushback_array((void***)cmd_array, (void*)cmd_ptr, g_global.num_cmds) == FAIL)
		return (FAIL);
	g_global.num_cmds++;
	*cmd_to_build = init_command();
	return (SUCCESS);
}

t_error	pushback_array(void ***array, void *new_elt, size_t array_size)
{
	void	**new_array;

	new_array = malloc(sizeof(void*) * (array_size + 1));
	if (!new_array)
		return (FAIL);
	ft_memcpy(new_array, *array, sizeof(void*) * array_size);
	new_array[array_size] = new_elt;
	free(*array);
	*array = new_array;
	return (SUCCESS);
}

void	free_array(void **ptr_array, int array_size)
{
	while (array_size-- > 0)
		free(ptr_array[array_size]);
	free(ptr_array);
}
