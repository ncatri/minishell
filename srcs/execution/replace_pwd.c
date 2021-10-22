#include "execution.h"

int replace_pwd(pwd_replace var)
{
	int index;
	char *pwd;
	char buff[PATH_MAX];

	if (var == PWD)
		index = find_key_index(g_global.envp, "PWD");
	else
		index = find_key_index(g_global.envp, "OLDPWD");
	delete_key(index);
	getcwd(buff, PATH_MAX);
	if (var == PWD)
		pwd = ft_strjoin("PWD=", buff);
	else
		pwd = ft_strjoin("OLDPWD=", buff);
	pushback_env((void ***)&g_global.envp, ft_strdup(pwd), number_of_split(g_global.envp));
	free(pwd);
	return (1);
}