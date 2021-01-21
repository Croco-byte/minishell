/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:21:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 13:59:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Affiche simplement le present working directory */

int	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (args_number(cmd) > 1)
	{
		ft_putendl_fd("pwd: too many arguments", STDERR);
		return (1);
	}
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		ft_putendl_fd("minishell: pwd: could not determine current directory: no such file or directory", STDERR);
		return (1);
	}
}
