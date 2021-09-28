#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_parser_state{
	START,
	COMMAND,
};

void	parser(t_list *token_list);
int		count_pipes(t_list *token_list);
t_command	init_command(void);
t_error	parse_analyzer(t_list *tok_cursor, t_command **cmd_array, t_command *command, enum e_parser_state *state);
t_error	pushback_array(t_command **cmd_array, t_command *cmd);
void	print_commands(t_command *cmds);

#endif
