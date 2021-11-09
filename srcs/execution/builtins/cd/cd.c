/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:17 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 09:24:41 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	cd_with_args(t_command *cmd)
{
	struct stat	stat_ret;

	if (find_key_index(g_global.envp, "OLDPWD") != -1)
		replace_pwd(OLDPWD);
	stat(cmd->args[0], &stat_ret);
	if (!S_ISDIR(stat_ret.st_mode))
		return (ret_msg("Directory doesn't exist\n", 0));
	chdir(cmd->args[0]);
	if (find_key_index(g_global.envp, "PWD") != -1)
		replace_pwd(PWD);
	return (1);
}

static int	cd_without_args(void)
{
	int			home_index;
	char		**split;

	if (find_key_index(g_global.envp, "OLDPWD") != -1)
		replace_pwd(OLDPWD);
	home_index = find_key_index(g_global.envp, "HOME");
	if (home_index != -1)
	{
		split = ft_split(g_global.envp[home_index], "=");
		chdir(split[1]);
		free_splits(split, number_of_split(split));
		if (find_key_index(g_global.envp, "PWD") != -1)
			replace_pwd(PWD);
		return (0);
	}
	else
	{
		g_global.ret = 1;
		return (ret_msg("HOME not set\n", 1));
	}
}

int	cd(t_command *cmd)
{
	if (cmd->number_args > 0)
	{
		cd_with_args(cmd);
		return (1);
	}
	else
	{
		if (cd_without_args() == 1)
			return (1);
	}
	g_global.ret = 0;
	return (1);
}
