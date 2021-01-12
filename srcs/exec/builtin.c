/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:35:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:37:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui redirige vers le bon builtin lorsqu'on a reçu une commande */

int	exec_builtin(t_minish *mini)
{
	int ret;

	ret = 0;
	if (ft_strcmp(mini->args[0], "pwd") == 0)
		ret = ft_pwd(mini);
	if (ft_strcmp(mini->args[0], "cd") == 0)
		ret = ft_cd(mini);
	if (ft_strcmp(mini->args[0], "echo") == 0)
		ret = ft_echo(mini);
	if (ft_strcmp(mini->args[0], "env") == 0)
		ft_env(mini);
	if (ft_strcmp(mini->args[0], "export") == 0)
		ft_export(mini);
	if (ft_strcmp(mini->args[0], "unset") == 0)
		ft_unset(mini);
	if (ft_strcmp(mini->args[0], "exit") == 0)
		ft_exit(mini);
	return (ret);
}
