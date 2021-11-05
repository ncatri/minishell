#include "lexer.h"

t_error	syntax_error(char c)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	write(2, &c, 1);
	write(2, "\n", 1);
	return (FAIL);
}

t_error	error_message(char *message)
{
	ft_putstr_fd(message, 2);
	return (FAIL);
}
