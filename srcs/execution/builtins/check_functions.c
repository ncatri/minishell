#include "execution.h"

int	check_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (-1);
	while (arg[i])
	{
		if (arg[i] == 'n')
			i++;
		else
			return (-1);
	}
	if (i == 1)
		return (-1);
	return (0);
}

int	exit_check(t_command *cmd)
{
	int	ret;

	ret = 0;
	if (full_digits(cmd->args[0]) == 0)
	{
		ret_msg("Exit : need numerics args\n", FAIL);
		g_global.ret = 255;
	}
	else if (cmd->number_args == 1)
		g_global.ret = ft_atoi(cmd->args[0]);
	else if (cmd->number_args > 1)
	{
		g_global.ret = 1;
		ret = ret_msg("Exit : too many arguments\n", 1);
	}
	else if (g_global.num_cmds < 2)
		printf("exit\n");
	return (ret);
}

int	valid_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isalpha(str[i]) && !isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	full_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
