#include "execution.h"

static void	push_var(t_command *cmd, int i, char **split)
{
	if (find_key_index(g_global.envp, split[0]) >= 0)
	{
		unset(cmd, i);
		pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), \
			number_of_split(g_global.envp));
	}
	else
		pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), \
			number_of_split(g_global.envp));
}

static int	check_if_arg(t_command *cmd)
{
	char	**sorted_env;

	if (cmd->number_args == 0)
	{
		sorted_env = alphasort(g_global.envp);
		env(sorted_env, EXPORT);
		free(sorted_env);
		return (1);
	}
	return (0);
}

int	export(t_command *cmd)
{
	char	**split;
	int		i;

	if (check_if_arg(cmd))
		return (1);
	i = 0;
	while (i < cmd->number_args)
	{
		if (cmd->args[i][0] == '=')
			return (ret_msg("bad identifier in the var\n", 1));
		split = ft_split(cmd->args[i], "=");
		if (split[0] == 0 || !valid_env_var(split[0]))
		{
			free_splits(split, number_of_split(split));
			return (ret_msg("bad identifier in the var\n", 1));
		}
		push_var(cmd, i, split);
		i++;
	}
	free_splits(split, number_of_split(split));
	g_global.ret = 0;
	return (1);
}
