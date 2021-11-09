/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:03 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:25:04 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*last_elt_of_path(char *path)
{
	char	*backslash;

	if (!path)
		return (NULL);
	backslash = ft_strrchr(path, '/');
	if (!backslash)
		return (path);
	else
		return (backslash + 1);
}

int	find_key_index(char **env, char *key)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], "=");
		if (ft_strcmp(split[0], key) == 0)
		{
			free_splits(split, number_of_split(split));
			return (i);
		}
		i++;
		free_splits(split, number_of_split(split));
	}
	return (-1);
}

static char	**create_env_paths(char **env)
{
	char	**tmp;
	char	**paths;
	int		index;

	index = find_key_index(env, "PATH");
	if (index == -1)
		return (NULL);
	tmp = ft_split(env[index], "=");
	paths = ft_split(tmp[1], ":");
	free_splits(tmp, number_of_split(tmp));
	return (paths);
}

static char	*join_cmd_to_path(char *path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*create_command_path(char **env, char *exec)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	paths = create_env_paths(env);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = join_cmd_to_path(paths[i], exec);
		if (open(cmd_path, O_RDONLY | O_EXCL) != -1)
		{
			free_splits(paths, number_of_split(paths));
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_splits(paths, number_of_split(paths));
	return (NULL);
}
