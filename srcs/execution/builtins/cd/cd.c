#include "execution.h"

int	cd(t_command *cmd)
{
	struct stat	stat_ret;

	if (cmd->number_args > 0)
	{
		replace_pwd(OLDPWD);
		stat(cmd->args[0], &stat_ret);
		if (!S_ISDIR(stat_ret.st_mode))
			return (printf("Directory doesn't exists\n"));
		chdir(cmd->args[0]);
		replace_pwd(PWD);
	}
	g_global.ret = 0;
	return (1);
}
