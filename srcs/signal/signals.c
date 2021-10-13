#include "signals.h"

void	setup_signals(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		printf("error tcgetattr\n");

	signal(SIGINT, signal_handler);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		printf("received SIGINT\n");
	else if (signal == SIGQUIT)
		printf("received SIGQUIT\n");
}
