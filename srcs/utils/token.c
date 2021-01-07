#include "minishell.h"

t_token	*next_separotor(t_token *token, int i)
{
	if (token && i)
		token = token->next;
	while (token && token->type < OUTFILE)
		token = token->next;
	return (token);
}

t_token	*next_cmd(t_token *token, int i)
{
	if (token && i)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token->type == CMD !token->prev)
			;
		else if (token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}
