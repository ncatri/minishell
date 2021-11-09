/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:25 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:27 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	wait_childs(void)
{
	int		status;
	pid_t	wait_return;

	wait_return = 1;
	while (wait_return > 0)
	{
		wait_return = wait(&status);
		if (WIFEXITED(status))
			g_global.ret = WEXITSTATUS(status);
	}
}

int	fill_pids(int fork_res, t_list *input, t_pid *pids, int i)
{
	pids[i].pid = fork_res;
	if (is_heredoc(input) == 1)
		pids[i].heredoc = 1;
	else
		pids[i].heredoc = 0;
	return (0);
}
