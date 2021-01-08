/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:08:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 12:56:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_var(t_minish *mini, int pos)
{
	int	i;
	int	j;
	int	var_nb;
	t_env	*new;

	i = 0;
	j = 0;
	var_nb = env_var_nb(mini->parsed_env);
	new = malloc((var_nb) * sizeof(t_env));
	while (i < pos)
	{
		new[j].key = ft_strdup(mini->parsed_env[i].key);
		new[j].value = ft_strdup(mini->parsed_env[i].value);
		i++;
		j++;
	}
	i++;
	while(mini->parsed_env[i].key)
	{
		new[j].key = ft_strdup(mini->parsed_env[i].key);
		new[j].value = ft_strdup(mini->parsed_env[i].value);
		i++;
		j++;
	}
	new[j].key = 0;
	free_parsed_env(mini->parsed_env);
	mini->parsed_env = new;
	mini->env = update_env(mini->env, mini->parsed_env);
}

int	ft_unset(t_minish *mini)
{
	int i;
	int	pos;

	i = 1;
	if (args_number(mini->args) < 2)
	{
		ft_putendl_fd("unset: not enough arguments", 1);
		return (ERROR);
	}
	while (i < args_number(mini->args))
	{
		pos = is_in_env(mini, mini->args[i]);
		if (pos != -1)
			del_env_var(mini, pos);
		i++;
	}
	return (SUCCESS);
}