/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:06 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:25:07 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**copy_env(char **envp)
{
	char	**copy;
	int		oldpwd_index;
	int		i;

	copy = malloc(sizeof(char *) * (number_of_split(envp) + 1));
	oldpwd_index = find_key_index(envp, "OLDPWD");
	i = 0;
	while (envp[i])
	{
		if (i == oldpwd_index)
			copy[i] = ft_strdup("OLDPWD");
		else
			copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_error	pushback_env(void ***array, void *new_elt, size_t array_size)
{
	void	**new_array;

	if (!array)
		return (FAIL);
	new_array = malloc(sizeof(void *) * (array_size + 2));
	if (!new_array)
		return (FAIL);
	ft_memcpy(new_array, *array, sizeof(void *) * array_size);
	new_array[array_size] = new_elt;
	new_array[array_size + 1] = 0;
	free(*array);
	*array = new_array;
	return (SUCCESS);
}

char	**alphasort(char **env)
{
	int		i;
	char	*temp;
	char	**copy;

	copy = malloc(number_of_split(env) * (sizeof(char *) + sizeof(char *)));
	if (!env || !*env || copy == NULL)
		return (NULL);
	i = -1;
	while (env[++i])
		copy[i] = env[i];
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
