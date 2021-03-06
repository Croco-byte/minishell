/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:47:27 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:44:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c && !is_escaped(line, *i + j))
		{
			c = ' ';
			j++;
		}
		else
			j++;
	}
	return (j - count + 1);
}

void	set_token_str(t_token *token, char *line, int *i)
{
	int		j;
	char	c;

	j = 0;
	c = ' ';
	while (line[*i] && (!ft_isspace(line[*i]) || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
		{
			token->str[j++] = line[(*i)];
			c = line[(*i)++];
		}
		else if (c != ' ' && line[*i] == c && !is_escaped(line, *i))
		{
			token->str[j++] = line[(*i)];
			c = ' ';
			(*i)++;
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token->str)
		return (0);
	set_token_str(token, line, i);
	return (token);
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
