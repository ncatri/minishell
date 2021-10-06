#ifndef EXECUTION_H
# define EXECUTION_H

# define WRITE (1)
# define READ (0)
# define CHILD (0)
# include "minishell.h"

typedef struct s_command
{
	char	*exec;
	char	**args;
	char	**input;
	char	**output;
} t_command;

typedef struct s_pid
{
	pid_t 	pid;
	int		heredoc;
} t_pid;
#endif
