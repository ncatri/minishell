#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h> // printf in lexer.c
# include "../libft/includes/libft.h"
typedef int t_error;
# define FAIL (0)
# define SUCCESS (1)
# include "lexer.h"
typedef enum pipes{
	CREATE = 1,
	CLOSE = 0,
} pipes;

#endif
