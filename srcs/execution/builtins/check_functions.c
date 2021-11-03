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

int	exit_check(t_command *cmd)
{
	int ret;

	ret = 0;
	
	if (full_digits(cmd->args[0]) == 0)
		ret_msg("Exit : need numerics args\n", FAIL);
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
