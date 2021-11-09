/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:37 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:39 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_command_array(t_command **cmd_array, int arr_size)
{
	int	i;

	i = 0;
	while (i < arr_size)
	{
		printf(" ** command %d **\n", i + 1);
		print_command(cmd_array[i]);
		i++;
	}
}

void	print_command(t_command *cmds)
{
	int		i;

	printf("executable: %s\n", cmds->executable);
	printf("args: ");
	i = -1;
	while (++i < cmds->number_args)
		printf(" %s |", cmds->args[i]);
	printf("\n");
	printf("input_redir: \n");
	print_redirin_list(cmds->input_redir);
	printf("output_redir: \n");
	print_redirout_list(cmds->output_redir);
}

void	print_redirout_list(t_list *redir_list)
{
	t_redir_out	*elt;
	t_list		*cursor;
	char		*mode;

	cursor = redir_list;
	while (cursor)
	{
		elt = cursor->content;
		if (elt->mode == CREATE)
			mode = "CREATE";
		else
			mode = "APPEND";
		printf(" %s (%s) |", elt->filename, mode);
		cursor = cursor->next;
	}
	printf("\n");
}

void	print_redirin_list(t_list *redir_list)
{
	t_redir_in	*elt;
	t_list		*cursor;
	char		*type;

	cursor = redir_list;
	while (cursor)
	{
		elt = cursor->content;
		if (elt->type == NORMAL_FILE)
			type = "NORMAL_FILE";
		else
			type = "HERE_DOC";
		printf(" %s (%s) |", elt->name_delim, type);
		cursor = cursor->next;
	}
	printf("\n");
}
