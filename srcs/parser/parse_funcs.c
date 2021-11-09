/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:26:41 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:26:42 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_error	parse_word(t_token *tok, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state)
{
	t_error	ret;

	(void)cmd_array;
	ret = SUCCESS;
	if (cmd_to_build->executable == NULL)
		cmd_to_build->executable = tok->data;
	else
	{
		ret = ft_pushback_array((void ***)&cmd_to_build->args, tok->data,
				cmd_to_build->number_args);
		cmd_to_build->number_args++;
	}
	*state = COMMAND_IN_PROGRESS;
	return (ret);
}

t_error	parse_pipe(t_list *tok_cursor, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state)
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

t_error	parse_redirection(t_list **tok_cursor, t_command *cmd_to_build, \
		enum e_parser_state *state)
{
	t_token	*tok;

	if ((*tok_cursor)->next == NULL)
	{
		printf("\x1B[31m error: unexpected end of line \x1B[0m\n");
		*state = ERROR;
		return (FAIL);
	}
	tok = (*tok_cursor)->next->content;
	if (tok->type != WORD)
	{
		g_global.ret = 258;
		printf("\x1B[31m error: unexpected token after file redirection\x1B[0m\n");
		*state = ERROR;
		return (FAIL);
	}
	tok = (*tok_cursor)->content;
	*state = COMMAND_IN_PROGRESS;
	if (tok->type == GREAT || tok->type == DGREAT)
		return (parse_output_redir(tok_cursor, cmd_to_build));
	else if (tok->type == LESS || tok->type == DLESS)
		return (parse_input_redir(tok_cursor, cmd_to_build));
	else
		return (FAIL);
}

t_error	parse_output_redir(t_list **tok_cursor, t_command *cmd_to_build)
{
	t_redir_out	*redir_out;	
	t_token		*tok;

	tok = (*tok_cursor)->content;
	redir_out = malloc(sizeof(t_redir_out));
	if (!redir_out)
		return (FAIL);
	if (tok->type == GREAT)
		redir_out->mode = CREATE;
	else
		redir_out->mode = APPEND;
	*tok_cursor = (*tok_cursor)->next;
	tok = (*tok_cursor)->content;
	redir_out->filename = tok->data;
	if (add_redir_to_list(&cmd_to_build->output_redir,
			(void *)redir_out) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_error	parse_input_redir(t_list **tok_cursor, t_command *cmd_to_build)
{
	t_redir_in	*redir_in;	
	t_token		*tok;

	tok = (*tok_cursor)->content;
	redir_in = malloc(sizeof(t_redir_in));
	if (!redir_in)
		return (FAIL);
	if (tok->type == LESS)
		redir_in->type = NORMAL_FILE;
	else
		redir_in->type = HERE_DOC;
	*tok_cursor = (*tok_cursor)->next;
	tok = (*tok_cursor)->content;
	redir_in->name_delim = tok->data;
	if (add_redir_to_list(&cmd_to_build->input_redir, (void *)redir_in) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
