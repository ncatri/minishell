#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include "minishell.h"

void	setup_main_signals(void);
void	main_signal_handler(int signal);
void	setup_cmd_signals(void);
void	cmd_signal_handler(int signal);

#endif
