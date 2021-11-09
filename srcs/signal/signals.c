/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:54 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:34:55 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	setup_terminal(void)
{
	struct termios	term_buff;

	if (tcgetattr(STDIN_FILENO, &g_global.term_save) == -1)
		printf("error tcgetattr\n");
	term_buff = g_global.term_save;
	term_buff.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_buff);
}

void	setup_main_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	handler(int signal)
{
	if ((signal == SIGQUIT || signal == SIGINT) && g_global.pid != 0)
		process(signal);
	else
	{
		if (signal == SIGINT)
		{
			new_prompt('\n', STDIN_FILENO);
			g_global.ret = 1;
		}
		if (signal == SIGQUIT)
		{
			ft_putchar_fd('\r', 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	process(int signal)
{
	if (kill(g_global.pid, signal) == 0)
	{
		if (signal == SIGINT)
			ft_putchar_fd('\n', 1);
		if (signal == SIGQUIT && g_global.heredoc == FALSE)
			ft_putstr_fd("Quit: 3\n", 1);
		if (open("heredoc.txt", O_RDONLY, 0644) >= 0)
		{
			unlink("heredoc.txt");
			if (signal == SIGINT)
				g_global.ret = 1;
		}
		else
			g_global.ret = 128 + signal;
	}
	else if (signal == SIGINT)
		new_prompt('\n', STDIN_FILENO);
	else if (signal == SIGQUIT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	new_prompt(char c, int fd)
{
	ft_putchar_fd(c, fd);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
