#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_parser_state{
	START,
	COMMAND,
};

void	parser(t_list *token_list);
t_command	init_command(void);
t_error	parse_analyzer(t_list *tok_cursor, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state);
t_error	pushback_array(t_command ***cmd_array, t_command *cmd_ptr);
t_error	push_command_to_array(t_command ***cmd_array, t_command *cmd_to_build);

void	free_array(void **ptr_array, int array_size);

/* debug */

void	print_command(t_command *cmds);
void	print_command_array(t_command **cmd_array, int arr_size);

#endif
