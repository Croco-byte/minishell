/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:47:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 11:12:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}
