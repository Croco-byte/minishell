/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:43:52 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:44:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	squish(t_minish *mini, t_token *token, t_token *prev)
{
	while (is_last_valid_arg(prev) == 0)
		prev = prev->prev;
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev)
		token->next = prev->next;
	else
	{
		token->next = mini->start;
		prev = token;
	}
	prev->next->prev = token;
	if (mini->start->prev)
		mini->start = mini->start->prev;
	else
		prev->next = token;
}

void	squish_args(t_minish *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (is_tok_type(token, ARG) && is_types(prev, "TAI"))
			squish(mini, token, prev);
		token = token->next;
	}
}
