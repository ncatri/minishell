#include "signals.h"

void	setup_signals(void)
{
	struct termios term_buff;

	if (tcgetattr(STDIN_FILENO, &g_global.term_save) == -1)
		printf("error tcgetattr\n");
	term_buff = g_global.term_save;
	term_buff.c_lflag |= ~ECHOCTL;
	term_buff.c_lflag |= ECHONL;
//	term_buff.c_lflag &= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_buff);

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		//printf("received SIGINT\n");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		printf("received SIGQUIT\n");
		exit(0);
	}
}
