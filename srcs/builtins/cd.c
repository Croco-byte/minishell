/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:36:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* La fonction CD qui prend une commande commençant par "cd", suivie par un seul argument, et change le working directory */

int	ft_cd(t_minish *mini)
{
	if (args_number(mini->args) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 1);
		return (1);
	}
	if (chdir(mini->args[1]) == -1)
	{
		ft_printf("%s : ", mini->args[0]);
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	return (0);
}
