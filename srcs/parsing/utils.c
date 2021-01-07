#include "minishell.h"

void	args_type(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	if (!separator)
	{
		if (ft_strcmp(token->str, ">") == 0)
			token->type = INFILE;
		else if (ft_strcmp(token->str, "<") == 0)
			token->type = OUTFILE;
		else if (ft_strcmp(token->str, ">>") == 0)
			token->type = APPEND;
		else if (ft_strcmp(token->str, "|") == 0)
			token->type = PIPE;
		else if (ft_strcmp(token->str, ";") == 0)
			token->type = END;
	}
	if (token->prev == NULL || token->prev->type != INFILE)
		token->type = CMD;
	else
		token->type = ARG;
}
