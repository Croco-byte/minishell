/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/10 14:29:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig sig;

void	minish_loop(t_minish *mini)
{
	char *line;
	int status;
	int	empty_EOF;

	status = 1;
	while(status)
	{
		sig.pid = 0;
		line = 0;
		mini->args = 0;
		ft_prompt();
		empty_EOF = get_next_line(STDIN_FILENO, &line);
		if (empty_EOF == -2)									// --> i.e si on a rencontré un EOF et que la ligne était vide.
		{
			free(line);
			free_strarray(mini->args);
			ft_putstr_fd("exit\n", 1);
			clean_exit(mini);
		}
		mini->args = parse_line(line);
		if (line)
			exec_cmd(mini);
		free(line);
		free_strarray(mini->args);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minish	mini;

	(void)argc;
	(void)argv;
	mini.args = 0;
	mini.env = 0;
	parse_env(&mini, env);
	mini.env = update_env(mini.env, mini.parsed_env);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	minish_loop(&mini);
	free_strarray(mini.env);
	free_parsed_env(mini.parsed_env);
	return (0);
}
