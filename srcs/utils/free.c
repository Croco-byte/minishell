/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:44:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 15:43:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_minish *mini)
{
	ft_putendl_fd("Bye ! 👋", 1);
	free_strarray(mini->env);
	free_parsed_env(mini->parsed_env);
	exit(0);
}

void	free_strarray(char **args)
{
	int i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_parsed_env(t_env *parsed_env)
{
	int i;

	i = 0;
	if (!parsed_env)
		return ;
	while (parsed_env[i].key)
	{
		free(parsed_env[i].key);
		free(parsed_env[i].value);
		i++;
	}
	free(parsed_env);
}
