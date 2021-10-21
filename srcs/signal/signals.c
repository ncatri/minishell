#include "signals.h"

void	setup_main_signals(void)
{
	struct termios term_buff;

	if (tcgetattr(STDIN_FILENO, &g_global.term_save) == -1)
		printf("error tcgetattr\n");
	term_buff = g_global.term_save;
	term_buff.c_lflag &= ~ECHOCTL;
//	term_buff.c_lflag |= ECHONL;
//	term_buff.c_lflag &= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_buff);

	signal(SIGINT, main_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	main_signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_cmd_signals(void)
{
	signal(SIGINT, cmd_signal_handler);
	signal(SIGQUIT, cmd_signal_handler);
}

void	cmd_signal_handler(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		printf("\n");
		return ;
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
}
