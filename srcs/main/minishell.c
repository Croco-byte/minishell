/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 16:53:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minish_loop(t_minish *mini)
{
	char *line;
	int status;

	status = 1;
	while(status)
	{
		signal(SIGINT, &sig_int);
		ft_prompt();
		get_next_line(STDIN_FILENO, &line);
		mini->args = parse_line(line);
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
	minish_loop(&mini);
	free_strarray(mini.env);
	free_parsed_env(mini.parsed_env);
	return (0);
}
