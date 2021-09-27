#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	parser(t_list *token_list);
int		count_pipes(t_list *token_list);

#endif
