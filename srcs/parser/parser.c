#include "parser.h"
#include "lexer.h"

/*	input: a list of tokens
 *	output: an array of pointer to commands
*/

void	parser(t_list *token_list)
{
	t_command			**cmd_array;
	t_command			cmd_to_build;
	t_list				*tok_cursor;
	enum e_parser_state state;

	print_token_list(token_list);
	g_global.num_cmds = 0;
	state = WAITING;
	tok_cursor = token_list;
	cmd_array = NULL;
	cmd_to_build = init_command();
	while (tok_cursor)
	{
		parse_analyzer(tok_cursor, &cmd_array, &cmd_to_build, &state);
		tok_cursor = tok_cursor->next;
	}
	if (state == COMMAND_IN_PROGRESS)
		push_command_to_array(&cmd_array, &cmd_to_build);
	print_command_array(cmd_array, g_global.num_cmds);
	free_array((void**)cmd_array, g_global.num_cmds);
}

t_error	parse_analyzer(t_list *tok_cursor, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state)
{
	t_token		*tok;

	if (!tok_cursor || !cmd_to_build || !state || !cmd_array)
		return (FAIL);
	tok = tok_cursor->content;

	if (tok->type == WORD)
		return (parse_word(tok, cmd_array, cmd_to_build, state));
	/*
	else if (tok->type == GREAT || tok->type == DGREAT)
		func_parse_redirout(tok, cmd_array, cmd_to_build)
	else if (tok->type == LESS || tok->type == DLESS)
		func_parse_redirin()
	*/
	else
		return (parse_pipe(tok, cmd_array, cmd_to_build, state));

}

t_command	init_command(void)
{
	t_command	cmd;

	cmd.executable = NULL;
	cmd.args = NULL;
	cmd.number_args = 0;
	cmd.input_redir = NULL;
	cmd.output_redir = NULL;
	return (cmd);
}
