/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:34 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:36 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_error	push_command_to_array(t_command ***cmd_array, t_command *cmd_to_build)
{
	t_command	*cmd_ptr;

	cmd_ptr = malloc(sizeof(t_command));
	if (!cmd_ptr)
		return (FAIL);
	ft_memcpy(cmd_ptr, cmd_to_build, sizeof(t_command));
	if (ft_pushback_array((void ***)cmd_array, (void *)cmd_ptr, \
				g_global.num_cmds) == FAIL)
		return (FAIL);
	g_global.num_cmds++;
	*cmd_to_build = init_command();
	return (SUCCESS);
}

void	free_array(void **ptr_array, int array_size)
{
	while (array_size-- > 0)
		free(ptr_array[array_size]);
	free(ptr_array);
}

t_error	add_redir_to_list(t_list **redir_list, void *redir)
{
	t_list	*new_elt;

	new_elt = ft_lstnew(redir);
	if (!new_elt)
		return (FAIL);
	ft_lstadd_back(redir_list, new_elt);
	return (SUCCESS);
}
