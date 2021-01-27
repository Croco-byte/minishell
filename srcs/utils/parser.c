/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:46:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 17:03:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && is_escaped(line, i) && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int	sep_after_backslashes(char *line, int i)
{
	while (line[i] && line[i] == '\\')
		i++;
	if (line[i] && (line[i] == '>' || line[i] == ';' || line[i] == '|'
			|| (line[i] == '>' && line[i + 1] && line[i + 1] == '>')))
		return (1);
	return (0);
}

int	nb_of_backslashes(char *line, int i)
{
	int	count;

	count = 0;
	while (line[i] && line[i] == '\\')
	{
		i++;
		count++;
	}
	return (count);
}

int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && sep_after_backslashes(line, i)
		&& nb_of_backslashes(line, i) % 2 != 0)
		return (1);
	return (0);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && is_escaped(line, i))
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_tok_type(token, CMD) || is_tok_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || is_tok_type(prev, END) || is_tok_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

void	tai_errors(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token « ", STDERR);
	if (token->next)
		ft_putstr_fd(token->next->str, STDERR);
	else
		ft_putstr_fd("newline", STDERR);
	ft_putendl_fd(" »", STDERR);
	g_status.code = 2;
}

void	pe_errors(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token « ", STDERR);
	ft_putstr_fd(token->str, STDERR);
	ft_putendl_fd(" »", STDERR);
	g_status.code = 2;
}

int	check_line(t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			tai_errors(token);
			return (0);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			pe_errors(token);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
