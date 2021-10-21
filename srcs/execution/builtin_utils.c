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

char **alphasort(char **env)
{
	int		i;
	char	*temp;
	char 	**copy;


	copy = malloc(number_of_split(env) * (sizeof(char *) + 1));
	i = 0;
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = 0;
	i = 0;
	while (i < number_of_split(env) - 1)
	{
		if (ft_strcmp(copy[i], copy[i + 1]) > 0)
		{
			temp = copy[i];
			copy[i] = copy[i + 1];
			copy[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (copy);
}

t_error	pushback_env(void ***array, void *new_elt, size_t array_size)
{
	void	**new_array;

	if (!array)
		return (FAIL);
	new_array = malloc(sizeof(void*) * (array_size + 2));
	if (!new_array)
		return (FAIL);
	ft_memcpy(new_array, *array, sizeof(void*) * array_size);
	new_array[array_size] = new_elt;
	new_array[array_size + 1] = 0;
	//free(*array);
	*array = new_array;
	return (SUCCESS);
}


int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->executable, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "env") == 0)
		return (1);
	//if (ft_strcmp(cmd->executable, "exit") == 0)
	//	return ();
	return (0);
}

int	check_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->executable, "cd") == 0)
		return (cd(cmd));
	if (ft_strcmp(cmd->executable, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(cmd->executable, "echo") == 0)
		return (echo(cmd));
	if (ft_strcmp(cmd->executable, "export") == 0)
		return (export(cmd));
	if (ft_strcmp(cmd->executable, "unset") == 0)
		return (unset(cmd, -1));
	if (ft_strcmp(cmd->executable, "env") == 0)
		return (env(g_global.envp, CLASSIC));
	//if (ft_strcmp(cmd->executable, "exit") == 0)
	//	return ();
	return (0);
}
