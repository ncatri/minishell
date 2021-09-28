#include "parser.h"
#include "lexer.h"

/*	input: a list of tokens
 *	output: an array of commands
*/

void	parser(t_list *token_list)
{
	t_command			*cmd_array;
	t_command			command;
	t_list				*tok_cursor;
	enum e_parser_state state;

	print_token_list(token_list);
	g_global.num_cmds = 0;
	state = START;
	tok_cursor = token_list;
	cmd_array = NULL;
	command = init_command();
	while (tok_cursor)
	{
		parse_analyzer(tok_cursor, &cmd_array, &command, &state);
		tok_cursor = tok_cursor->next;
	}
	print_commands(cmd_array);
	free(cmd_array);
}

t_error	parse_analyzer(t_list *tok_cursor, t_command **cmd_array, t_command *command, enum e_parser_state *state)
{
	t_token	*tok;

	if (!tok_cursor || !command || !state || !cmd_array)
		return (FAIL);
	tok = tok_cursor->content;
	if (tok->type == WORD && *state == START)
	{
		command->command = tok->data;
		*state = COMMAND;
	}
	if (!tok_cursor->next || tok->type == PIPE)
	{
		pushback_array(cmd_array, command);
		g_global.num_cmds++;
		*state = START;
	}
	return (SUCCESS);
}

t_error	pushback_array(t_command **cmd_array, t_command *cmd)
{
	t_command	*new_array;

	new_array = malloc(sizeof(t_command) * (g_global.num_cmds + 1));
	if (!new_array)
		return (FAIL);
	ft_memcpy(new_array, *cmd_array, sizeof(t_command) * g_global.num_cmds);
	new_array[g_global.num_cmds] = *cmd;
	free(*cmd_array);
	*cmd_array = new_array;
	return (SUCCESS);
}

void	print_commands(t_command *cmds)
{
	int i;

	i = 0;
	while (i < g_global.num_cmds)
	{
		printf(" ** command %d **\n", i + 1);
		printf("cmd name: %s\n", cmds[i].command);
		printf("args:  %p\n", cmds[i].args);
		printf("input_redir:  %p\n", cmds[i].input_redir);
		printf("output_redir:  %p\n", cmds[i].output_redir);
		i++;
	}
}

t_command	init_command(void)
{
	t_command	cmd;

	cmd.command = NULL;
	cmd.args = NULL;
	cmd.input_redir = NULL;
	cmd.output_redir = NULL;
	return (cmd);
}

int	count_pipes(t_list *token_list)
{
	t_token	*tok;
	t_list	*cursor;
	int		count;

	count = 0;
	cursor = token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->type == PIPE)
			count++;
		cursor = cursor->next;
	}
	return (count);
}
