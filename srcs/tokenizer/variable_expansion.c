#include "lexer.h"

t_error	expand_variables(t_list *token_list)
{
	t_list *cursor;
	t_token	*tok;

	cursor = token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->type == WORD)
			expansion(&tok->data);
		cursor = cursor->next;
	}
	return (SUCCESS);
}

t_error	expansion(char **string)
{
	char	*cursor;
	char	**split;
	char	*after_var;
	char	*variable;

	cursor = ft_strchr(*string, '$');
	while (cursor && *cursor)
	{
		if (*(cursor + 1) && *(cursor + 1) != ' ')
		{
			split = ft_split(cursor, "$ \'\"");
			if (split[0])
			{
				after_var = cursor + ft_strlen(split[0]) + 1;
				variable = getenv(split[0]);
				printf("cursor: (%s), variable: (%s), after: (%s)\n", cursor, variable, after_var);
				if (rebuild_string(string, cursor, variable, after_var) == FAIL)
					return (FAIL);
			}
			free_split(split);
			cursor = ft_strchr(*string, '$');
		}
		else
			cursor = ft_strchr(cursor + 1, '$');
	}
	return (SUCCESS);
}

t_error	rebuild_string(char **string, char *middle, char *variable, char *after)
{
	char	*begining;
	char	*new_string;
	char	*tmp;

	if (variable == NULL)
		variable = "";
	begining = malloc(sizeof(char) * (middle - *string + 1));
	if (!begining)
		return (FAIL);
	ft_memcpy(begining, *string, middle - *string);
	begining[middle - *string] = '\0';
	tmp = ft_strjoin(begining, variable);
	new_string = ft_strjoin(tmp, after);
	if (!tmp || !new_string)
		return (FAIL);
	free(tmp);
	free(begining);
	free(*string);
	*string = new_string;
	return (SUCCESS);
}
