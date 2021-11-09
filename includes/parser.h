/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourmau <lfourmau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:24:49 by lfourmau          #+#    #+#             */
/*   Updated: 2021/11/09 07:24:51 by lfourmau         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

enum e_parser_state{
	WAITING,
	COMMAND_IN_PROGRESS,
	FINISHED,
	ERROR,
};

t_command	**parser(t_list *token_list);
t_command	init_command(void);
t_error		parse_analyzer(t_list **tok_cursor, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state);
t_error		push_command_to_array(t_command ***cmd_array, \
		t_command *cmd_to_build);
void		free_array(void **ptr_array, int array_size);
t_error		parse_word(t_token *tok, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state);
t_error		parse_pipe(t_list *tok_cursor, t_command ***cmd_array, \
		t_command *cmd_to_build, enum e_parser_state *state);
t_error		parse_redirection(t_list **tok_cursor, t_command *cmd_to_build, \
		enum e_parser_state *state);
t_error		parse_output_redir(t_list **tok_cursor, t_command *cmd_to_build);
t_error		parse_input_redir(t_list **tok_cursor, t_command *cmd_to_build);
t_error		add_redir_to_list(t_list **redir_list, void *redir);
char		*last_elt_of_path(char *path);
void		parsing_error(t_command ***cmd_array, enum e_parser_state *state);
void		free_cmd(t_command *cmd);

/* debug */

void		print_command(t_command *cmds);
void		print_command_array(t_command **cmd_array, int arr_size);
void		print_redirout_list(t_list *redir_list);
void		print_redirin_list(t_list *redir_list);

#endif
