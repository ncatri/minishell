#include "execution.h"

int	pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
		return (printf("Error on the pwd\n"));
	else
		printf("%s\n", buff);
	g_global.ret = 0;
	return (1);
}
