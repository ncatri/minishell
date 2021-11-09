/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:11 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:12 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

t_bool	is_executable(char *cmd_exec)
{
	struct stat	file;

	if (stat(cmd_exec, &file) == 0 && file.st_mode & S_IXUSR)
		return (TRUE);
	return (FALSE);
}

void	final_exec(t_command **commands, int i)
{
	if (is_builtin(commands[i]))
	{
		if (check_builtin(commands[i]))
			exit(0);
		else
			exit (1);
	}
	else
	{
		execve(commands[i]->executable, commands[i]->args, g_global.envp);
		exit(1);
	}
}

void	verif_exec(t_command *cmd, char **env)
{
	if (open(cmd->executable, O_RDONLY) == -1 && \
		!ft_strchr(cmd->executable, '/'))
		cmd->executable = create_command_path(env, cmd->executable);
	else if (open(cmd->executable, O_RDONLY) != -1 \
		&& ft_strchr(cmd->executable, '/'))
		;
	else
		cmd->executable = NULL;
	if (open(cmd->executable, O_DIRECTORY) >= 0)
		cmd->executable = NULL;
	if (cmd->executable != NULL && \
	(open(cmd->executable, O_RDONLY) == -1 || !is_executable(cmd->executable)))
	{
		g_global.ret = 126;
		ft_putstr_fd("\x1B[31mPermission denied\n\033[0m", 2);
		exit(g_global.ret);
	}
}
