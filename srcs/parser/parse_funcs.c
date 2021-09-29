#include "parser.h"
#include "lexer.h"

t_error	parse_word(t_token *tok, t_command ***cmd_array, t_command *cmd_to_build,
		enum e_parser_state *state)
{
	(void)cmd_array;
	t_error	ret;

	ret = SUCCESS;
	if (cmd_to_build->executable == NULL)
		cmd_to_build->executable = tok->data;
	else
	{
		ret = pushback_array((void***)&cmd_to_build->args, tok->data, cmd_to_build->number_args);
		cmd_to_build->number_args++;
	}
	*state = COMMAND_IN_PROGRESS;
	return (ret);
}

t_error	parse_pipe(t_list *tok_cursor, t_command ***cmd_array, t_command *cmd_to_build,
		enum e_parser_state *state)
{
	t_error	ret;

	if (*state != COMMAND_IN_PROGRESS || tok_cursor->next == NULL)	
	{
		printf("pipe: parsing error\n");
		ret = FAIL;
	}
	else
	{
		ret = push_command_to_array(cmd_array, cmd_to_build);
		*state = WAITING;
	}
	return (ret);
}
