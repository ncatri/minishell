#include "execution.h"

int	export(t_command *cmd)
{
	char	**sorted_env;
	char	**split;
	int		i;

	if (cmd->number_args == 0)
	{
		sorted_env = alphasort(g_global.envp);
		env(sorted_env, EXPORT);
		free(sorted_env);
		return (1);
	}
	i = 0;
	while (i < cmd->number_args)
	{
		split = ft_split(cmd->args[i], "=");
		if (split[0] == 0 || !valid_env_var(split[0]))
		{
			free_splits(split, number_of_split(split)); //delete this line if bugs
			return(ret_msg("bad identifier in the var\n", 1));
		}
		if (find_key_index(g_global.envp, split[0]) >= 0)
		{
			unset(cmd, i);
			pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), \
				number_of_split(g_global.envp));
		}
		else
			pushback_env((void ***)&g_global.envp, ft_strdup(cmd->args[i]), \
				number_of_split(g_global.envp));
		i++;
	}
	free_splits(split, number_of_split(split));
	g_global.ret = 0;
	return (1);
}