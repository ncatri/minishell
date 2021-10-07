#ifndef EXECUTION_H
# define EXECUTION_H

# define WRITE (1)
# define READ (0)
# define CHILD (0)
# include "minishell.h"

typedef struct s_cmd
{
	char	*exec;
	char	**args;
	char	**input;
	char	**output;
} t_cmd;

typedef struct s_pid
{
	pid_t 	pid;
	int		heredoc;
} t_pid;

typedef enum pipes{
	INITIALIZE,
	DESTROY,
} pipes;

int		find_previous_hd(t_pid *pid, int i);
int		is_heredoc(char **input);
int		heredoc(char *terminator, int fd);
int		browse_inputs(char **input_cmd);
int		connect_input_pipe(int i, char **input, int pipesfd[][2]);
int		connect_output_pipe(int i, int nb_cmds, char **output, int pipesfd[][2]);
int		wait_previous_heredoc(char **input, t_pid *pids, int i);
int		input_redirection(char **input);
int		output_redirection(char **outputs);

#endif
