/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mooves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:56 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:00 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**delete_loop(char **new, int index)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < index)
	{
		new[j] = strdup(g_global.envp[i]);
		j++;
	}
	i++;
	while (g_global.envp[i])
	{
		new[j] = strdup(g_global.envp[i]);
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

int	delete_key(int index)
{
	char	**new;

	if (index == -1)
		return (0);
	new = malloc(sizeof(char *) * (number_of_split(g_global.envp)));
	if (new == NULL)
		return (-1);
	new = delete_loop(new, index);
	if (new == NULL)
		return (-1);
	free_splits(g_global.envp, number_of_split(g_global.envp));
	g_global.envp = new;
	return (0);
}

char	**sep_key_operations(char *equal, char *str, char **ret)
{
	char	*term;

	term = ft_strchr(str, 0);
	ret = malloc(sizeof(char *) * 3);
	if (ret == NULL)
		return (NULL);
	ret[0] = malloc(sizeof(char) * (equal - str + 1));
	if (ret[0] == NULL)
		return (NULL);
	ft_memcpy(ret[0], str, (equal - str));
	ret[0][equal - str] = 0;
	ret[1] = malloc(sizeof(char) * (term - (equal + 1) + 1));
	if (ret[1] == NULL)
		return (NULL);
	ft_memcpy(ret[1], (equal + 1), (term - (equal + 1)));
	ret[1][term - (equal + 1)] = 0;
	ret[2] = NULL;
	return (ret);
}

char	**sep_key_value(char *str, char c)
{
	char	*equal;
	char	**ret;

	ret = NULL;
	equal = ft_strchr(str, c);
	if (equal == NULL)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	return (sep_key_operations(equal, str, ret));
}
