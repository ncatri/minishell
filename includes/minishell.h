#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h> // printf in lexer.c

# include "lexer.h"
# include "libft.h"
//# include "lexer.h"
//# include "parser.h"

struct s_global{
	int	num_cmds;
};

struct s_global g_global;

typedef struct s_command{
	char	*executable;
	char	**args;
	int		number_args;
	t_list	*input_redir;
	t_list	*output_redir;

}				t_command;

enum e_file_type {NORMAL_FILE, HERE_DOC};
enum e_output_mode {CREATE, APPEND};

typedef struct s_input_redirect{
	enum e_file_type	type;
	char 				*name_delim;
}				t_redir_in;

typedef struct s_output_redirect{
	enum e_output_mode	mode;
	char 				*filename;
}				t_redir_out;

#endif
