/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 15:44:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* La fonction CD qui prend une commande commençant par "cd", suivie par un seul argument, et change le working directory */

int	ft_cd(char **cmd)
{
	if (args_number(cmd) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 1);
		return (1);
	}
	if (chdir(cmd[1]) == -1)
	{
		ft_printf("%s : ", cmd[0]);
		ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	return (0);
}
