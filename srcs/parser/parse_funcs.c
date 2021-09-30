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
		printf("\x1B[31mpipe: parsing error\x1B[0m\n");
		ret = FAIL;
		*state = ERROR;
	}
	else
	{
		ret = push_command_to_array(cmd_array, cmd_to_build);
		*state = WAITING;
	}
	return (ret);
}

t_error	parse_redirout(t_list **tok_cursor, t_command *cmd_to_build, 
		enum e_parser_state *state)
{
	t_redir_out	*redir_out;	
	t_token		*tok;

	if ((*tok_cursor)->next == NULL)
	{
		printf("\x1B[31mredirection: missing file\x1B[0m\n");
		*state = ERROR;
		return (FAIL);
	}
	redir_out = malloc(sizeof(t_redir_out));
	if (!redir_out)
		return (FAIL);
	tok = (*tok_cursor)->content;
	if (tok->type == GREAT)
		redir_out->mode = CREATE;
	else
		redir_out->mode = APPEND;
	*tok_cursor = (*tok_cursor)->next;
	tok = (*tok_cursor)->content;
	redir_out->filename = tok->data;
	if (add_redir_to_list(&cmd_to_build->output_redir, (void*)redir_out) == FAIL)
		return (FAIL);
	*state = COMMAND_IN_PROGRESS;
	return (SUCCESS);
}

t_error	parse_redirin(t_list **tok_cursor, t_command *cmd_to_build, 
		enum e_parser_state *state)
{
	t_redir_in	*redir_in;	
	t_token		*tok;

	if ((*tok_cursor)->next == NULL)
	{
		printf("\x1B[31mredirection: missing file\x1B[0m\n");
		*state = ERROR;
		return (FAIL);
	}
	redir_in = malloc(sizeof(t_redir_in));
	if (!redir_in)
		return (FAIL);
	tok = (*tok_cursor)->content;
	if (tok->type == LESS)
		redir_in->type = NORMAL_FILE;
	else
		redir_in->type = HERE_DOC;
	*tok_cursor = (*tok_cursor)->next;
	tok = (*tok_cursor)->content;
	redir_in->name_delim = tok->data;
	if (add_redir_to_list(&cmd_to_build->input_redir, (void*)redir_in) == FAIL)
		return (FAIL);
	*state = COMMAND_IN_PROGRESS;
	return (SUCCESS);
}

t_error	add_redir_to_list(t_list **redir_list, void *redir)
{
	t_list	*new_elt;

	new_elt = ft_lstnew(redir);
	if (!new_elt)
		return (FAIL);
	ft_lstadd_back(redir_list, new_elt);
	return (SUCCESS);
}
