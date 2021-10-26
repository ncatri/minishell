#include "execution.h"

int check_n(char *arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'n')
			i++;
		else
			return (-1);
	}
	return (0);
}