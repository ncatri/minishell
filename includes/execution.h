#ifndef EXECUTION_H
# define EXECUTION_H

# define WRITE (1)
# define READ (0)
# define CHILD (0)
# define PATHMAX (1024)
# include "minishell.h"
#include <sys/stat.h>


typedef struct s_pid
{
	pid_t 	pid;
	int		heredoc;
} t_pid;

typedef enum pipes{
	INITIALIZE,
	DESTROY,
} pipes;

int			find_previous_hd(t_pid *pid, int i);
int			is_heredoc(t_list *input);
int			heredoc(char *terminator, int fd);
t_error		browse_inputs(t_list *input_cmd);
t_error		connect_input_pipe(int i, t_list *input, int pipesfd[][2]);
t_error		connect_output_pipe(int i, t_list *output, int pipesfd[][2]);
int			wait_previous_heredoc(t_list *input, t_pid *pids, int i);
t_error		input_redirection(t_list *input);
t_error		output_redirection(t_list *outputs);
int			fill_pids(int fork_res, t_list *input, t_pid *pids, int i);
void		wait_childs();
int			allpipes_action(int pipesfd[][2], int nb_pipes, pipes action);
t_error		execution(t_command **commands, char **env);
void		free_splits(char **chain, int i);
int			number_of_split(char **splitresult);
char		*create_command_path(char **env, char *exec);
void 		print_array(char **array, size_t arr_len);
int			check_builtin(t_command *cmd);

#endif
