/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 15:57:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minish_loop(void)
{
	char *line;
	char **args;
	int status;

	args = 0;
	status = 1;
	while(status)
	{
		ft_prompt();
		get_next_line(STDIN_FILENO, &line);
		args = parse_line(line);
		exec_cmd(args);

		free(line);
		free_args(args);
	}
}


int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	minish_loop();
	return (0);
}
