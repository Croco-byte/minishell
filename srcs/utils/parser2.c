/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:47:03 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:47:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
