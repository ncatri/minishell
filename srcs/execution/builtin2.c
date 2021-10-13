#include "execution.h"

int delete_key(int index)
{
	char **new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (number_of_split(g_global.envp)));
	if (new == NULL)
		return (-1);
	while (i < index)
	{
		new[j] = g_global.envp[i];
		i++;
		j++;
	}
	i++;
	while (g_global.envp[i])
	{
		new[j] = g_global.envp[i];
		i++;
		j++;
	}
	new[j] = 0;
	g_global.envp = new;
	return (0);
}

int unset(t_command *cmd)
{
	int i;
	int index;

	i = 0;
	while (i < cmd->number_args)
	{
		index = find_key_index(g_global.envp, cmd->args[i]);
		if (index != -1)
			delete_key(index);
		i++;
	}
	return (1);
}

char **alphasort(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < number_of_split(env) - 1)
	{
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (env);
}

int	export(t_command *cmd)
{
	char **sorted_env;
	int i;

	i  = 0;
	if (cmd->number_args == 0)
	{
		sorted_env = alphasort(g_global.envp);
		while (sorted_env[i])
		{
			printf("declare -x %s\n", sorted_env[i]);
			i++;
		}
	}
	return (1);
}