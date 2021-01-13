#include "minishell.h"

void	arg_type(t_token *token, int sep)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && sep == 0)
		token->type = OUTFILE;
	else if(ft_strcmp(token->str, ">>") == 0 && sep == 0)
		token->type = APPEND;	
	else if (ft_strcmp(token->str, "<") == 0 && sep == 0)
		token->type = INFILE;
	else if(ft_strcmp(token->str, "|") == 0 && sep == 0)
		token->type = PIPE;	
	else if (ft_strcmp(token->str, ";") == 0 && sep == 0)
		token->type = END;
	else if(token->prev == NULL || token->prev->type >= OUTFILE)
		token->type = CMD;
	else
		token->type = ARG;
}

int	next_alloc(char *line, int *i)
{
	int	count;
	int	j;
	char	c;

	count = 0;
	j = -1;
	c = ' ';
	while (line[*i + (++j)] && (line[*i + (++j)] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
		}
		if (line [*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

t_token	*next_token(char *line, int *i)
{
	t_token *token;
	int	j;
	char	c;

	j = 0;
	c =' ';
	if (!(token = malloc(sizeof(t_token))) || !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}


t_token	*get_tokens(char *line)
{
	t_token *prev;
	t_token *next;
	int	sep;
	int	i;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = i_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		arg_type(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	_args(t_minish *mini)
{
	t_token *token;
	t_token *prev;

	token = mini->start;
	while (token)
	{
		prev = prev_separator(token, NOSKIP);
		if (_type(token, ARG) && _types(prev, "OAI"))
		{
			while (valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next =  token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = (prev) ? prev->next : mini->start;
			prev = (prev) ? prev : token;
			prev->next->prev = token;
			prev->next = (mini->start->prev) ? prev->next : token;
			mini->start = (mini->start->prev) ? mini->start->prev : mini->start;
		}
		token = token->next;
	}
}

