/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:48:23 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:51:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_strarray(char **strarray)
{
	int	i;

	i = 0;
	if (!strarray)
		return ;
	while (strarray[i])
	{
		ft_putstr_fd("[", STDERR);
		ft_putnbr_fd(i, STDERR);
		ft_putstr_fd("] = ", STDERR);
		ft_putstr_fd(strarray[i], STDERR);
		ft_putstr_fd(" -- ", STDERR);
		i++;
	}
	ft_putstr_fd("\n", STDERR);
}

void	display_chained_list(t_minish *mini)
{
	while (mini->start->next)
	{
		printf("%s [TYPE %i] ; ", mini->start->str, mini->start->type);
		mini->start = mini->start->next;
	}
	printf("%s [TYPE %i] ", mini->start->str, mini->start->type);
	printf("\n");
	while (mini->start && mini->start->prev)
		mini->start = mini->start->prev;
}
