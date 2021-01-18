/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:47:40 by user42            #+#    #+#             */
/*   Updated: 2021/01/14 15:46:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_tok_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int		is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_tok_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && is_tok_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_tok_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_tok_type(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && is_tok_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_tok_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_tok_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_tok_type(token, END))
		return (1);
	return (0);
}

int		has_type(t_token *token, int type)
{
	while (token)
	{
		if (is_tok_type(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

int		has_pipe(t_token *token)
{
	while (token && is_tok_type(token, END) == 0)
	{
		if (is_tok_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}
