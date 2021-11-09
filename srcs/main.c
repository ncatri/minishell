/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:27:30 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 09:09:40 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*main_loop(char **line)
{
	setup_terminal();
	g_global.pid = 0;
	setup_main_signals();
	g_global.heredoc = FALSE;
	*line = readline("\033[0;32mminishell ===> \033[0m");
	if (*line == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
		printf("exit\n");
		exit(g_global.ret);
	}
	return (*line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*token_list;
	t_command	**cmd_array;

	(void)argv;
	g_global.envp = copy_env(envp);
	g_global.ret = 0;
	if (argc != 1)
		return (printf("\x1B[31mToo much args\n\033[0m"));
	while (1)
	{
		line = main_loop(&line);
		add_history(line);
		token_list = tokenizer(line);
		cmd_array = parser(token_list);
		if (cmd_array)
			execution(cmd_array);
		ft_lstclear(&token_list, free_token);
		free_loop(line, cmd_array);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_global.term_save);
	}
	free_splits(g_global.envp, number_of_split(g_global.envp));
	return (0);
}
