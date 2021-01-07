#include "minishell.h"

int	_type(t_token *token, int type)
{
	if (token)
	{
		if (token->type == type)
			return (1);
		return (0);
	}
	return (0);
}

int	_types(t_token *token, char *types)
{
	if (ft_strchr(types, 'I') && _type(token, INFILE))
		return (1);
	else if (ft_strchr(types, 'O') && _type(token, OUTFILE))
		return (1);
	else if (ft_strchr(types, 'A') && _type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'P') && _type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && _type(token, END))
		return (1);
	else if (ft_strchr(types, 'C') && _type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'a') && _type(token, ARG))
		return (1);
	else if (ft_strchr(types, ' ') && _type(token, EMPTY))
		return (1);
	else
		return (0);
}

int	__pipe(t_token *token)
{
	while (token && _type(token, END) == 0)
	{
		if (_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
		
int	__type(t_token *token, int type)
{
	while (token)
	{
		if (_type(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token *prev_separator(t_token *token, int i)
{
	if (token && i)
		token = token->prev;
	while (token && token->type < OUTFILE)
	       token = token->prev;
	return (token);
}	
