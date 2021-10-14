#include "execution.h"

int cd(t_command *cmd)
{
	struct stat stat_ret;

	stat(cmd->args[0], &stat_ret);
	if (!S_ISDIR(stat_ret.st_mode))
		return (printf("Directory doesn't exists\n"));
	chdir(cmd->args[0]);
	return (1);
	//need to change env vars (pwd and oldpwd)
}

int pwd()
{
	char buff[PATHMAX];
	
	if (getcwd(buff, PATHMAX) == NULL)
		return (printf("Error on the pwd\n"));
	else
		printf("%s\n", buff);
	return (1);
}

int echo(t_command *cmd)
{
	int i;
	int newline;

	i = 0;
	newline = ft_strncmp(cmd->args[0], "-n", 2);
	if (newline == 0)
		i = 1;
	while (i < cmd->number_args)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline != 0)
		printf("\n");
	return (1);
}

int env(char **envp, env_status status)
{
	int i;
	char **export_print;

	i = 0;
	while (envp[i])
	{
		if (status == EXPORT)
		{
			export_print = ft_split(envp[i], "=");
			printf("declare -x ");
			printf("%s", export_print[0]);
			if (ft_strchr(envp[i], '='))
			{
				printf("=\"");
				if (export_print[1])
					printf("%s\"\n", export_print[1]);
				else
					printf("\"\n");
			}
			else
				printf("\n");
		}
		else if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return(1);
}
