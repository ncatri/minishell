#ifndef LEXER_H
# define LEXER_H

# include <stdio.h> // printf
# include "minishell.h"

enum e_token_types{
	WORD,	// cmd, option, args, files
	LESS,	// <
	DLESS,	// <<
	GREAT,	// >
	DGREAT, // >>
	PIPE	// |
};

typedef struct s_token{
	enum e_token_types	type;
	char				*data;
}				t_token;

enum e_machine_states{
	ST_START,
	ST_IN_WORD,
	ST_OPEN_SQUOTE,
	ST_OPEN_DQUOTE,
};

int	tokenizer(char *line);

#endif
