#include "execution.h"

char *join_option(int len)
{
	int i;
	char *option;

	i = 1;
	option = malloc(sizeof(char) * (len + 1));
	option[0] = '-';
	while (i < len - 1)
	{		
		option[i] = 'n';
		i++;
	}
	option[i] = 0;
	return (option);
}