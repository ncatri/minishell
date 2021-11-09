/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:24:45 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:24:47 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "libft.h"
# include "signals.h"

struct s_global{
	int				num_cmds;
	int				ret;
	char			**envp;
	struct termios	term_save;
	pid_t			pid;
	t_bool			heredoc;
};

struct s_global	g_global;

typedef struct s_command{
	char	*executable;
	char	**args;
	int		number_args;
	t_list	*input_redir;
	t_list	*output_redir;

}				t_command;

enum e_file_type {
	NORMAL_FILE,
	HERE_DOC
};

enum e_output_mode {
	CREATE,
	APPEND
};

typedef struct s_input_redirect{
	enum e_file_type	type;
	char				*name_delim;
}				t_redir_in;

typedef struct s_output_redirect{
	enum e_output_mode	mode;
	char				*filename;
}				t_redir_out;

#endif
