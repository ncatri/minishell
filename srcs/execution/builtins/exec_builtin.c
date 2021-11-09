/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:52 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 09:15:07 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->executable)
		return (0);
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
	if (ft_strcmp(cmd->executable, "exit") == 0)
		return (1);
	return (0);
}

int	check_builtin(t_command *cmd)
{
	if (!cmd->executable)
		return (0);
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
	if (ft_strcmp(cmd->executable, "exit") == 0)
	{
		if (exit_check(cmd) == 0)
			exit(g_global.ret);
		return (1);
	}
	return (0);
}
