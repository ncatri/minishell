#ifndef LEXER_H
# define LEXER_H

# include <stdio.h> // printf
# include "minishell.h"

typedef struct s_buffer{
	char	*buf;
	size_t	size;
	size_t	pos;
	int		n_squote;
	int		n_dquote;
}				t_buffer;
# define BUF_SIZE (1)

enum e_token_types{
	WORD,	// cmd, option, args, files
	LESS,	// <
	DLESS,	// <<
	GREAT,	// >
	DGREAT, // >>
	PIPE	// |
};

# define INVALID_WORD_CHAR "&();"

typedef struct s_token{
	int		type;
	char	*data;
}				t_token;

enum e_machine_states{
	ST_TRANSITION,
	ST_IN_WORD,
	ST_OPEN_SQUOTE,
	ST_OPEN_DQUOTE,
	ST_LESS,
	ST_GREAT,
};
# define NUM_OF_STATES (6)

t_list	*tokenizer(char *line);
t_error	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	initialize_buffer(t_buffer *buffer);
t_error	append_buffer(t_buffer *buffer, char c);
t_token *new_token(enum e_token_types type, char *buf);
void	free_token(void *token);
t_error	add_token_to_list(t_list **token_list, int token_type, char *data);
t_error	syntax_error(char c);

/* tableau pointeurs sur fonction */

t_error	f_inword(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_doublequote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_singlequote(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_less(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_great(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);

void	set_machine_state(char cursor, enum e_machine_states *state);

/* debug */

void	print_token_list(t_list *token_list);
void	print_token(t_token *token);


#endif
