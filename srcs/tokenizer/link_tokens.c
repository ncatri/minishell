#include "lexer.h"

t_error	link_tokens(t_list *token_list)
{
	t_list	*cursor;
	t_token	*tok;
	t_token	*tok_next;
	char	*str;

	cursor = token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->concat_next)
		{
			str = tok->data;
			tok_next = cursor->next->content;
			str = ft_strjoin(str, tok_next->data);
			free(tok_next->data);
			tok_next->data = str;
			ft_lstdelnode(&token_list, cursor, free_token);
		}
		cursor = cursor->next;
	}
	return (SUCCESS);
}

t_error	expand_words(t_list *token_list)
{
	t_list	*cursor;
	t_token	*tok;

	cursor = token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->type == WORD)
			variable_expansion(tok->data);
		cursor = cursor->next;
	}
	return (SUCCESS);
}

void	variable_expansion(char *data)
{
	char	*start;
	char	*end;
	char	*tmp;

	start = ft_strchr(data, '$');
	if (start)
	{
		end = start;
		while (*end && *end != ' ')
			end++;
		tmp = malloc(sizeof(char) * (end - start));
		if (!tmp)
			return;
		ft_strlcpy(tmp, start, (end - start));
		printf("%s\n", tmp);
	}
}
