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

struct s_token{
	enum e_token_types	type;
	char				*data;
};

int	tokenizer(char *line);

#endif
