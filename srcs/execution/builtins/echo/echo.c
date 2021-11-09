/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:25:23 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:25:25 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	if (cmd->number_args == 0)
		return (printf("\n"));
	while (i < cmd->number_args && check_n(cmd->args[i]) != -1)
		i++;
	if (i > 0)
		newline = 1;
	while (i < cmd->number_args)
	{
		printf("%s", cmd->args[i]);
		if (i < (cmd->number_args - 1))
			printf(" ");
		i++;
	}
	if (newline == 0)
		printf("\n");
	g_global.ret = 0;
	return (1);
}
