#include "execution.h"

int unset(t_command *cmd, int id)
{
	int i;
	int index;

	i = 0;
	if (id != -1)
	{
		index = find_key_index(g_global.envp, cmd->args[id]);
		if (index != -1)
			delete_key(index);
		return (1);
	}
	while (i < cmd->number_args)
	{
		index = find_key_index(g_global.envp, cmd->args[i]);
		if (index != -1)
			delete_key(index);
		i++;
	}
	return (1);
}
//need to free in pushback ? pb in export OK=
int	export(t_command *cmd)
{
	char **sorted_env;
	char **split;
	int i;

	if (cmd->number_args == 0)
	{
		sorted_env = alphasort(g_global.envp);
		env(sorted_env, EXPORT);
		free(sorted_env);
		return (1);
	}
	i  = 0;
	while (i < cmd->number_args)
	{
		split = ft_split(cmd->args[i], "=");
		if (find_key_index(g_global.envp, split[0]) >= 0)
		{
			unset(cmd, i);
			pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), number_of_split(g_global.envp));
		}
		else
			pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), number_of_split(g_global.envp));
		i++;
	}
	free_splits(split, number_of_split(split));
	return (1);
}

void	my_exit()
{
	printf("exit\n");
	exit(g_global.ret);
}