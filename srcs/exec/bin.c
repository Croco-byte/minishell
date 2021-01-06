/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:48:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 16:59:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bin(t_minish *mini)
{
	int pid;
	int wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(mini->args[0], mini->args) == -1)
		{
			ft_printf("%s : ", mini->args[0]);
			ft_putendl_fd(strerror(errno), 1);
		}
		exit(ERROR);
	}
	else if (pid < 0)
		ft_putendl_fd("Error forking", 1);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
}
