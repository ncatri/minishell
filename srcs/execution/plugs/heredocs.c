/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:16 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:17 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	find_previous_hd(t_pid *pid, int i)
{
	i--;
	while (i >= 0)
	{
		if (pid[i].heredoc == 1)
			return (i);
		i--;
	}
	return (-1);
}

t_bool	is_heredoc(t_list *input_list)
{
	t_list		*cursor;
	t_redir_in	*input;

	cursor = input_list;
	while (cursor)
	{
		input = cursor->content;
		if (input->type == HERE_DOC)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

int	wait_previous_heredoc(t_list *input_list, t_pid *pids, int i)
{
	int	previous_hd;

	if (is_heredoc(input_list))
	{
		previous_hd = find_previous_hd(pids, i);
		if (previous_hd != -1)
		{
			if (waitpid(pids[previous_hd].pid, 0, 0) == -1)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int	heredoc(char *terminator, int fd)
{
	char	*line;

	setup_terminal();
	line = NULL;
	fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (FAIL);
	while (get_next_line(READ, &line) != 0 && ft_strncmp(line, terminator, \
		ft_strlen(terminator)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
	fd = open("heredoc.txt", O_RDONLY, 0644);
	if (fd == -1)
		return (FAIL);
	return (fd);
}
