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
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_check(t_command *cmd)
{
	int ret;
	int i;

	ret = 0;
	if (cmd->number_args == 1)
	{
		if (valid_char_exit(cmd->args[0]) == 0)
			ret_msg("Exit : need numerics args\n", FAIL);
		g_global.ret = ft_atoi(cmd->args[0]);
	}
	if (cmd->number_args > 1)
	{
		i = 0;
		while (i < cmd->number_args)
		{
			if (valid_char_exit(cmd->args[i]) == 0)
				return (ret_msg("Exit : need numerics args\n", FAIL));
			i++;
		}
		g_global.ret = 1;
		ret = ret_msg("Exit : too many arguments\n", 1);
	}
	else
		printf("exit\n");
	return (ret);
}

int valid_env_var(char *str)
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

char **sep_key_value(char *str, char c)
{
	char *equal;
	char *term;
	char **ret;

	equal = ft_strchr(str, c);
	if (equal == NULL)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	term = ft_strchr(str, 0);
	ret = malloc(sizeof(char *) * 3);
	ret[0] = malloc(sizeof(char) * (equal - str + 1));
	ft_memcpy(ret[0], str, (equal - str));
	ret[0][equal - str] = 0;
	ret[1] = malloc(sizeof(char) * (term - (equal + 1) + 1));
	ft_memcpy(ret[1], (equal + 1), (term - (equal + 1)));
	ret[1][term - (equal + 1)] = 0;
	ret[2] = NULL;
	return (ret);
}
