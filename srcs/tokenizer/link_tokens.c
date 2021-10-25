#include "lexer.h"

t_error	link_tokens(t_list **token_list)
{
	t_list	*cursor;
	t_list	*to_be_deleted;
	t_token	*tok;
	t_token	*tok_next;
	char	*str;

	cursor = *token_list;
	while (cursor)
	{
		tok = cursor->content;
		if (tok->concat_next)
		{
			str = ft_strdup(tok->data); // copy current data
			tok_next = cursor->next->content; // go to next token
			str = ft_strjoin(str, tok_next->data); // join current data with next token's
			free(tok_next->data); // on libere next data
			tok_next->data = str; // la nouvelle chaine est attribuee au next token
			to_be_deleted = cursor;
			cursor = cursor->next;
			ft_lstdelnode(token_list, to_be_deleted, free_token); // on essaye de suppr current token
		}
		else
			cursor = cursor->next;
	}
	return (SUCCESS);
}
