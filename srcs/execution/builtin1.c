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

int	check_builtin(t_command *cmd)
{
	if (ft_strncmp(cmd->executable, "cd", 2) == 0)
		return (cd(cmd));
	if (ft_strncmp(cmd->executable, "pwd", 3) == 0)
		return (pwd());
	if (ft_strncmp(cmd->executable, "echo", 4) == 0)
		return (echo(cmd));
	//if (ft_strncmp(cmd->executable, "export", 6) == 0)
	//	return ();
	//if (ft_strncmp(cmd->executable, "unset", 5) == 0)
	//	return ();
	//if (ft_strncmp(cmd->executable, "env", 3) == 0)
	//	return ();
	//if (ft_strncmp(cmd->executable, "exit", 4) == 0)
	//	return ();
	return (0);
}