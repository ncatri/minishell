#include "execution.h"

static int export_call(int id, t_command *cmd)
{
	int index;
	char **split;

	if (id != -1)
	{
		split = ft_split(cmd->args[id], "=");
		if (!valid_env_var(split[0]))
			return (ret_msg("Bad identifier in the var\n", 1));
		index = find_key_index(g_global.envp, split[0]);
		free_splits(split, number_of_split(split));
		if (index != -1)
			delete_key(index);
		return (1);
	}
	return (0);
}

int	unset(t_command *cmd, int id)
{
	int	i;
	int	index;

	i = 0;
	if (export_call(id, cmd))
		return (1);
	while (i < cmd->number_args)
	{
		if (!valid_env_var(cmd->args[i]))
			return (ret_msg("Bad identifier in the var\n", 1));
		index = find_key_index(g_global.envp, cmd->args[i]);
		if (index != -1)
			delete_key(index);
		i++;
	}
	g_global.ret = 0;
	return (1);
}