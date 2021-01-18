/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:35:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 15:45:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui redirige vers le bon builtin lorsqu'on a reçu une commande */

int	exec_builtin(t_minish *mini, char **cmd)
{
	int ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ret = ft_pwd(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		ret = ft_cd(cmd);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ret = ft_echo(cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(mini, cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(mini, cmd);
	if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(mini, cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(mini, cmd);
	return (ret);
}
