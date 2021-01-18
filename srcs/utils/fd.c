/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:27:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 11:30:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_minish *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_minish *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

void	reset_fds(t_minish *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
}
