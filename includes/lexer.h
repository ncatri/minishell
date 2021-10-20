#ifndef LEXER_H
# define LEXER_H

# include <stdio.h> // printf
# include "minishell.h"
# include "libft.h"

typedef struct s_buffer{
	char	*buf;
	size_t	size;
	size_t	pos;
}				t_buffer;
# define BUF_SIZE (1)

enum e_token_types{
	WORD,	// cmd, option, args, files
	WORD_NOEXPAND,
	LESS,	// <
	DLESS,	// <<
	GREAT,	// >
	DGREAT, // >>
	PIPE	// |
};
# define NUM_OF_TOKENS (7) /* Needed for parser */

# define INVALID_WORD_CHAR "&();"

typedef struct s_token{
	int		type;
	char	*data;
	t_bool	concat_next;
}				t_token;

enum e_machine_states{
	ST_TRANSITION,
	ST_IN_WORD,
	ST_OPEN_SQUOTE,
	ST_OPEN_DQUOTE,
	ST_LESS,
	ST_GREAT,
	ST_WORD_TRANSITION,
};
# define NUM_OF_STATES (7)

enum e_add_space{
	NO_SPACE = 0,
	YES_SPACE = 1,
};

t_list	*tokenizer(char *line);
t_error	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	initialize_buffer(t_buffer *buffer);
t_error	append_buffer(t_buffer *buffer, char c);
t_token *new_token(enum e_token_types type, char *buf);
void	free_token(void *token);
t_error	add_token_to_list(t_list **token_list, int token_type, char *data);
t_error	syntax_error(char c);
t_error	error_message(char *message);
t_error	push_buf_to_toklist(t_buffer *buffer, t_list **token_list, enum e_token_types tok_type);
t_error	expand_buffer_push_toklist(t_buffer *buffer, t_list **token_list, int add_space);

/* tableau pointeurs sur fonction */

t_error	f_inword(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_doublequote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_singlequote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_less(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_great(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_var_expansion_dquote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);

void	set_machine_state(char cursor, enum e_machine_states *state);

void	link_last_token(t_list *token_list);
t_error	f_word_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);

/* post processing of tokens */

t_error	link_tokens(t_list *token_list);

/* variable substitution */

t_error	expand_variables(t_list *token_list);
t_error	expansion(char **string);
t_error	rebuild_string(char **string, char *middle, char *variable, char *after);

/* debug */

void	print_token_list(t_list *token_list);
void	print_token(t_token *token);


#endif
