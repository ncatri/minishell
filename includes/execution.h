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

typedef enum env_status{
	CLASSIC,
	EXPORT,
} env_status;

//Heredocs
int			find_previous_hd(t_pid *pid, int i);
int			is_heredoc(t_list *input);
int			heredoc(char *terminator, int fd);
int			wait_previous_heredoc(t_list *input, t_pid *pids, int i);
//Pipes
t_error		connect_input_pipe(int i, t_list *input, int pipesfd[][2]);
t_error		connect_output_pipe(int i, t_list *output, int pipesfd[][2]);
int			allpipes_action(int pipesfd[][2], int nb_pipes, pipes action);
//Inputs and outputs
t_error		browse_inputs(t_list *input_cmd);
t_error		input_redirection(t_list *input);
t_error		output_redirection(t_list *outputs);
//Builtins
int			check_builtin(t_command *cmd);
int			find_key_index(char **env, char *key);
int 		env();
int 		unset(t_command *cmd, int id);
int 		delete_key(int index);
char 		**alphasort(char **env);
int			check_builtin(t_command *cmd);
int 		cd(t_command *cmd);
int 		pwd();
int 		echo(t_command *cmd);
int	is_builtin(t_command *cmd);
t_error		pushback_env(void ***array, void *new_elt, size_t array_size);
//Utils
int			fill_pids(int fork_res, t_list *input, t_pid *pids, int i);
void		wait_childs();
t_error		execution(t_command **commands);
char		*create_command_path(char **env, char *exec);
void		free_splits(char **chain, int i);
int			number_of_split(char **splitresult);
void 		print_array(char **array, size_t arr_len);
int			export();


#endif
