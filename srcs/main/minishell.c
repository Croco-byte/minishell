/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 13:09:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	g_status;

void	redir_and_exec(t_minish *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_tok_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_tok_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_tok_type(prev, INPUT))
		input(mini, token);
	else if (is_tok_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_tok_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_tok_type(prev, END) || is_tok_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	pipe_vars_reset(t_minish *mini)
{
	mini->charge = 1;
	mini->parent = 1;
	mini->last = 1;
}

void	minish(t_minish *mini)
{
	t_token	*token;
	int		exit_code;

	token = next_run(mini->start, NOSKIP);
	if (is_types(mini->start, "TAI"))
		token = mini->start->next;
	while (token)
	{
		pipe_vars_reset(mini);
		redir_and_exec(mini, token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &exit_code, 0);
		if (mini->last == 0)
			g_status.code = WEXITSTATUS(exit_code);
		if (mini->parent == 0)
		{
			free_token(mini->start);
			exit(g_status.code);
		}
		mini->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

void	minish_loop(t_minish *mini)
{
	while (1)
	{
		g_status.pid = 0;
		mini->start = 0;
		parse(mini);
		if (mini->start && check_line(mini->start))
			minish(mini);
		free_token(mini->start);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minish	mini;

	(void)argc;
	(void)argv;
	g_status.code = 0;
	mini_init(&mini, env);
	increase_shell_level(&mini);
	sig_init();
	minish_loop(&mini);
	return (0);
}
