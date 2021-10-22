#include "execution.h"

char **copy_env(char **envp)
{
	char 	**copy;
	int 	i;

	copy = malloc(sizeof(char *) * (number_of_split(envp) + 1));
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}