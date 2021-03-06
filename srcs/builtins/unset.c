/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:08:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 13:35:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_var(t_minish *mini, int pos)
{
	int		i;
	int		j;
	int		var_nb;
	t_env	*new;

	i = 0;
	j = 0;
	var_nb = env_var_nb(mini->parsed_env);
	new = malloc((var_nb) *sizeof(t_env));
	while (i < pos)
	{
		new[j].key = ft_strdup(mini->parsed_env[i].key);
		new[j++].value = ft_strdup(mini->parsed_env[i++].value);
	}
	i++;
	while (mini->parsed_env[i].key)
	{
		new[j].key = ft_strdup(mini->parsed_env[i].key);
		new[j++].value = ft_strdup(mini->parsed_env[i++].value);
	}
	new[j].key = 0;
	free_parsed_env(mini->parsed_env);
	mini->parsed_env = new;
	mini->env = update_env(mini->env, mini->parsed_env);
}

int	ft_unset(t_minish *mini, char **cmd)
{
	int	i;
	int	pos;
	int	error_happened;

	i = 1;
	error_happened = 0;
	while (i < args_number(cmd))
	{
		if (cmd[i][0] == '\0')
		{
			ft_putstr_fd("minishell: export: not valid", STDERR);
			ft_putstr_fd(" in this context: ", STDERR);
			ft_putendl_fd(cmd[i], STDERR);
			error_happened = 1;
		}
		pos = is_in_env(mini, cmd[i]);
		if (pos != -1)
			del_env_var(mini, pos);
		i++;
	}
	return (error_happened);
}
