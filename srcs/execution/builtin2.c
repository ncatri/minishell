#include "execution.h"

char **delete_key(int index)
{
	char **new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (number_of_split(g_global.envp)));
	if (new == NULL)
		return (NULL);
	printf("{%d}\n" ,index);
	while (i < index)
	{
		new[j] = g_global.envp[i];
		printf("[%d]\n", i);
		i++;
		j++;
	}
	i++;
	while (g_global.envp[i])
	{
		new[j] = g_global.envp[i];
		printf("[%d]\n", i);
		i++;
		j++;
	}
	new[j] = 0;
	g_global.envp = new;
	return (new);
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