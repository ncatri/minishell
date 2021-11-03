#include "execution.h"

int	delete_key(int index)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (number_of_split(g_global.envp)));
	if (new == NULL)
		return (-1);
	while (i < index)
	{
		new[j] = strdup(g_global.envp[i]);
		i++;
		j++;
	}
	i++;
	while (g_global.envp[i])
	{
		new[j] = strdup(g_global.envp[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	free_splits(g_global.envp, number_of_split(g_global.envp));
	g_global.envp = new;
	return (0);
}

int	is_builtin(t_command *cmd)
{
	if (!cmd->executable)
		return (0);
	if (ft_strcmp(cmd->executable, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->executable, "exit") == 0)
		return (1);
	return (0);
}


int	check_builtin(t_command *cmd)
{
	if (!cmd->executable)
		return (0);
	if (ft_strcmp(cmd->executable, "cd") == 0)
		return (cd(cmd));
	if (ft_strcmp(cmd->executable, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(cmd->executable, "echo") == 0)
		return (echo(cmd));
	if (ft_strcmp(cmd->executable, "export") == 0)
		return (export(cmd));
	if (ft_strcmp(cmd->executable, "unset") == 0)
		return (unset(cmd, -1));
	if (ft_strcmp(cmd->executable, "env") == 0)
		return (env(g_global.envp, CLASSIC));
	if (ft_strcmp(cmd->executable, "exit") == 0)
	{
		if (exit_check(cmd) == 0)
			exit(g_global.ret);
		return (1);
	}
	return (0);
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
