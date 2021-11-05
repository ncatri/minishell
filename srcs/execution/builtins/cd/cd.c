#include "execution.h"

int	cd(t_command *cmd)
{
	struct stat	stat_ret;

	if (cmd->number_args > 0)
	{
		if (find_key_index(g_global.envp, "OLDPWD") != -1)
			replace_pwd(OLDPWD);
		stat(cmd->args[0], &stat_ret);
		if (!S_ISDIR(stat_ret.st_mode))
			return (ret_msg("Directory doesn't exist\n", 0));
		chdir(cmd->args[0]);
		if (find_key_index(g_global.envp, "PWD") != -1)
			replace_pwd(PWD);
	}
	g_global.ret = 0;
	return (1);
}
