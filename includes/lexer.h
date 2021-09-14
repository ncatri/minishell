#ifndef LEXER_H
# define LEXER_H

# include <stdio.h> // printf
# include "minishell.h"

# define BUF_SIZE (1)

typedef struct s_buffer{
	char	*buf;
	size_t	size;
	size_t	pos;
}				t_buffer;

enum e_token_types{
	WORD,	// cmd, option, args, files
	LESS,	// <
	DLESS,	// <<
	GREAT,	// >
	DGREAT, // >>
	PIPE	// |
};

typedef struct s_token{
	int		type;
	char	*data;
}				t_token;

enum e_machine_states{
	ST_TRANSITION,
	ST_IN_WORD,
	ST_OPEN_SQUOTE,
	ST_OPEN_DQUOTE,
};
# define NUM_OF_STATES (4)

t_error	tokenizer(char *line);
t_error	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	initialize_buffer(t_buffer *buffer);
t_error	append_buffer(t_buffer *buffer, char c);
t_token *new_token(enum e_token_types type, char *buf);

/* tableau pointeurs sur fonction */

t_error	f_inword(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
t_error	f_transition(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);

/* debug */

void	print_token_list(t_list *token_list);
void	print_token(t_token *token);


#endif
