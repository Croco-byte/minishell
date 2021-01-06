/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:35:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 16:21:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
}
