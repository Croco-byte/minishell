/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:21:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 11:42:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_minish *mini)
{
	char	cwd[PATH_MAX];

	if (args_number(mini->args) > 1)
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (ERROR);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
	{
		ft_putendl_fd("[Cwd not found]", 1);
		return (ERROR);
	}
}
