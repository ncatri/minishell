#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include "minishell.h"

void	setup_signals(void);
void	signal_handler(int signal);

#endif
