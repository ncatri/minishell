#include "parser.h"

void	print_command_array(t_command **cmd_array, int arr_size)
{
	int	i;

	i = 0;
	while (i < arr_size)
	{
		printf(" ** command %d **\n", i + 1);
		print_command(cmd_array[i]);
		i++;
	}
}

void	print_command(t_command *cmds)
{
	printf("executable: %s\n", cmds->executable);
	printf("args:  %p\n", cmds->args);
	printf("input_redir:  %p\n", cmds->input_redir);
	printf("output_redir:  %p\n", cmds->output_redir);
}
