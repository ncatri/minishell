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
	return (0);
}

int	valid_char_exit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			if (!str[i + 1] || str[i + 1] != '=')
				return (0); //call the func to join
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_check(t_command *cmd)
{
	int ret;

	ret = 0;
	if (cmd->number_args == 1)
	{
		if (valid_char_exit(cmd->args[0]) == 0)
			ret_msg("Exit : need numerics args\n", FAIL);
		g_global.ret = ft_atoi(cmd->args[0]);
	}
	if (cmd->number_args > 1)
	{
		g_global.ret = 1;
		ret = ret_msg("Exit : too many arguments\n", 1);
	}
	else
		printf("exit\n");
	return (ret);
}

int valid_unset_var(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!isalpha(str[i]) && !isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

