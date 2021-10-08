#ifndef EXECUTION_H
# define EXECUTION_H

# define WRITE (1)
# define READ (0)
# define CHILD (0)
# include "minishell.h"

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
int		is_heredoc(t_list *input);
int		heredoc(char *terminator, int fd);
int		browse_inputs(t_list *input_cmd);
int		connect_input_pipe(int i, t_list *input, int pipesfd[][2]);
int		connect_output_pipe(int i, t_list *output, int pipesfd[][2]);
int		wait_previous_heredoc(t_list *input, t_pid *pids, int i);
int		input_redirection(t_list *input);
int		output_redirection(t_list *outputs);
int		fill_pids(int fork_res, t_list *input, t_pid *pids, int i);
void	wait_childs();
int		allpipes_action(int pipesfd[][2], int nb_pipes, pipes action);
int		execution(t_command **commands);

#endif
