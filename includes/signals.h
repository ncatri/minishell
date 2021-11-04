#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include "minishell.h"

void	setup_terminal(void);
void	setup_main_signals(void);
void	handler(int signal);
void	process(int signal);
void	new_prompt(char c, int fd);

#endif
