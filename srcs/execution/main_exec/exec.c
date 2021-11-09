/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:07 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:09 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	**create_pipesfd(int nb_pipes)
{
	int	**pipesfd;
	int	i;

	pipesfd = malloc(sizeof(int *) * nb_pipes);
	if (pipesfd == NULL)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipesfd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (pipesfd);
}

int	single_builtin(t_pid *pids, t_command **commands)
{
	if (g_global.num_cmds == 1 && !commands[0]->output_redir)
	{
		if (check_builtin(commands[0]) == 1)
		{
			free(pids);
			return (SUCCESS);
		}
	}
	return (0);
}

int	finish_loop(int **pipesfd, int nb_pipes, t_pid *pids)
{
	if (allpipes_action(pipesfd, nb_pipes, DESTROY) == FAIL)
		return (FAIL);
	free(pids);
	wait_childs();
	return (SUCCESS);
}

int	before_loop(t_pid *pids, int **pipesfd, int nb_pipes, t_command **commands)
{
	if (pids == NULL || pipesfd == NULL)
		return (FAIL);
	if (allpipes_action(pipesfd, nb_pipes, INITIALIZE) == FAIL)
		return (FAIL);
	if (single_builtin(pids, commands) == SUCCESS)
	{
		allpipes_action(pipesfd, nb_pipes, DESTROY);
		return (0);
	}
	return (1);
}

t_error	execution(t_command **commands)
{
	int		nb_pipes;
	int		**pipesfd;
	t_pid	*pids;
	pid_t	fork_res;
	int		i;

	nb_pipes = g_global.num_cmds - 1;
	pipesfd = create_pipesfd(nb_pipes);
	pids = malloc(g_global.num_cmds * sizeof(t_pid));
	if (before_loop(pids, pipesfd, nb_pipes, commands) == 0)
		return (0);
	i = -1;
	while (++i < g_global.num_cmds)
	{
		fork_res = fork_and_wait_hd(commands, i, pids, fork_res);
		if (fork_res == CHILD)
			child_stuff(i, commands, nb_pipes, pipesfd);
		else if (fork_res > 0)
			fill_pids(fork_res, commands[i]->input_redir, pids, i);
		else
			return (FAIL);
	}
	if (finish_loop(pipesfd, nb_pipes, pids) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
