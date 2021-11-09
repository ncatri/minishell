/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:28 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:25:30 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	print_var(char **export_print, char **envp, int i)
{
	printf("declare -x ");
	printf("%s", export_print[0]);
	if (ft_strchr(envp[i], '='))
	{
		printf("=\"");
		if (export_print[1])
			printf("%s\"\n", export_print[1]);
		else
			printf("\"\n");
	}
	else
		printf("\n");
}

int	env(char **envp, t_env_status status)
{
	int		i;
	char	**export_print;

	i = 0;
	if (!envp || !*envp)
		return (1);
	while (envp[i])
	{
		if (status == EXPORT)
		{
			export_print = sep_key_value(envp[i], '=');
			print_var(export_print, envp, i);
			free_splits(export_print, number_of_split(export_print));
		}
		else if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	g_global.ret = 0;
	return (1);
}
