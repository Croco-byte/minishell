#include "minishell.h"


int	quotes(char *line, int index)
{
	int i;
	int j;

	i = 0;
	j = 0; //open simple quotes = 2, close simple or double quotes = 0, open double quotes=1
	while (line[i] && i != index)
	{
		if (i > 0 && line [i - 1] == '\\'); //escape backslash
		else if (j == 0 && line[i] == '\"')
			j = 1;
		else if (j == 1 && line[i] == '\"')
			j = 0;
		else if (j == 2 && line[i] == '\'')
			j = 0;
		else if (j == 0 && line[i] == '\'')
			j = 2;
		i++;
	}
	return (j);
}

int	sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<|>;", line[i]))
		return (0);
	else if(ft_strchr("<|>;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int	i_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1])
	{
		if (line[i + 1] == '>' && line[i + 2] == '>')
			return (1);
		else if (line[i + 1] == ';' || line[i + 1] == '|' || line[i + 1] == '>')
		       return (1);
	}	
	return (0);
}

int	checkline(t_token *token)
{
	while (token)
	{
		if (_types(token, "IAO") && _types(token->next, "POAIE"))
		{
			ft_putstr_fd("minishell : parse error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) : 0;
			ft_putendl_fd("'", STDERR);
			return(0);
		}
		if (_types(token, "PE") && (_types(token->prev, "POAIE")))
		{
			ft_putstr_fd("minishell : parse error near unexpected token `", STDERR);
			token->next ? ft_putstr_fd(token->next->str, STDERR) : 0;
			ft_putendl_fd("'", STDERR);
			return(0);
		}
		token = token->next;
	}
	return (1);
}

int	valid_arg(t_token *token)
{
	t_token *prec;

	if (_type(token, CMD) || _type(token, ARG) || !token)
	{
		prec = prev_separator(token, NOSKIP);
		if (!prec || _type(prec, END) || _type(prec, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

	
