#include "execution.h"

int	echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	if (cmd->number_args == 0)
		return (printf("\n"));
	while (check_n(cmd->args[i]) != -1)
		i++;
	if (i > 0)
		newline = 1;
	while (i < cmd->number_args)
	{
		printf("%s", cmd->args[i]);
		if (i < (cmd->number_args - 1))
			printf(" ");
		i++;
	}
	if (newline == 0)
		printf("\n");
	g_global.ret = 0;
	return (1);
}
