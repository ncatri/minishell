#ifndef LEXER_H
# define LEXER_H

# include <stdio.h> // printf
# include "minishell.h"

# define BUF_SIZE (10)

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
	ST_START,
	ST_IN_WORD,
	ST_OPEN_SQUOTE,
	ST_OPEN_DQUOTE,
};

int	tokenizer(char *line);
void	analyzer(char cursor, enum e_machine_states *state, t_list **token_list, t_buffer *buffer);
void	print_token_list(t_list *token_list);
t_bool	ft_isspace(int c);
void	print_token(t_token *token);
void	initialize_buffer(t_buffer *buffer);
void	append_buffer(t_buffer *buffer, char c);
t_token *new_token(enum e_token_types type, char *buf);

#endif
