/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:24:33 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:24:35 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define WRITE (1)
# define READ (0)
# define CHILD (0)
# define PATH_MAX (1024)
# include "minishell.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_pid
{
	pid_t	pid;
	int		heredoc;
}	t_pid;

typedef enum pipes{
	INITIALIZE,
	DESTROY,
}	t_pipes;

typedef enum env_status{
	CLASSIC,
	EXPORT,
}	t_env_status;

typedef enum pwd_replace{
	OLDPWD,
	PWD,
}	t_pwd_replace;

//Heredocs
int			is_heredoc(t_list *input);
int			heredoc(char *terminator, int fd);
int			find_previous_hd(t_pid *pid, int i);
int			wait_previous_heredoc(t_list *input, t_pid *pids, int i);
//Pipes
t_error		connect_input_pipe(int i, t_list *input, int **pipesfd);
t_error		connect_output_pipe(int i, t_list *output, int **pipesfd);
int			allpipes_action(int **pipesfd, int nb_pipes, t_pipes action);
//Inputs and outputs
t_error		browse_inputs(t_list *input_cmd);
t_error		input_redirection(t_list *input);
t_error		output_redirection(t_list *outputs);
t_error		connections(int i, t_command *cmd, int **pipesfd);
//Builtins
int			pwd(void);
int			check_n(char *arg);
int			cd(t_command *cmd);
int			echo(t_command *cmd);
int			delete_key(int index);
int			export(t_command *cmd);
char		**alphasort(char **env);
int			is_builtin(t_command *cmd);
int			replace_pwd(t_pwd_replace var);
int			check_builtin(t_command *cmd);
int			unset(t_command *cmd, int id);
int			check_builtin(t_command *cmd);
int			env(char **envp, t_env_status status);
int			find_key_index(char **env, char *key);
t_error		pushback_env(void ***array, void *new_elt, size_t array_size);
//Utils
void		wait_childs(void);
char		**copy_env(char **envp);
t_error		execution(t_command **commands);
void		free_splits(char **chain, int i);
int			number_of_split(char **splitresult);
void		print_array(char **array, size_t arr_len);
char		*create_command_path(char **env, char *exec);
void		free_loop(char *line, t_command **cmd_array);
int			fill_pids(int fork_res, t_list *input, t_pid *pids, int i);
int			ret_msg(char *message, int return_status);
int			full_digits(char *str);
int			exit_check(t_command *cmd);
int			valid_env_var(char *str);
char		**sep_key_value(char *str, char c);
t_bool		is_executable(char *cmd_exec);
//execution
void		final_exec(t_command **commands, int i);
int			build_exec(t_command *cmd, char **env);
int			child_stuff(int i, t_command **commands, \
	int nb_pipes, int **pipesfd);
pid_t		fork_and_wait_hd(t_command **commands, \
	int i, t_pid *pids, int fork_res);
void		verif_exec(t_command *cmd, char **env);
t_bool		is_executable(char *cmd_exec);
#endif
