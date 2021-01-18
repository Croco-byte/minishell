/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:02:30 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 16:56:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_init(t_minish *mini, char **env)
{
	mini->env = 0;
	parse_env(mini, env);
	mini->env = update_env(mini->env, mini->parsed_env);
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->fdin = -1;
	mini->fdout = -1;
	mini->no_exec = 0;
}

void	sig_init(void)
{
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
}
