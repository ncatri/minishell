#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h> // printf in lexer.c
# include "libft.h"


typedef int t_error;
# define FAIL (0)
# define SUCCESS (1)

# include "lexer.h"
# include "parser.h"

typedef struct s_simple_command{
	char	*command;
	char	**args;
	t_list	*input_files_redir;
	t_list	*output_files_redir;

}				t_simple_command;

#endif
