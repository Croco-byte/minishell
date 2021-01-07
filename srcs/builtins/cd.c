/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 11:41:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minish *mini)
{
	if (args_number(mini->args) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 1);
		return (ERROR);
	}
	if (chdir(mini->args[1]) == -1)
	{
		ft_printf("%s : ", mini->args[0]);
		ft_putendl_fd(strerror(errno), 1);
		return (ERROR);
	}
	return (SUCCESS);
}
