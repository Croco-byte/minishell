/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:08:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 15:42:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Unset : quand on reçoit une commande commençant par "unset", on vérifie que l'argument passé correspond bien à une variable d'environnement (si non, pas d'erreur,
mais on ne fait rien). Si l'argument passé correspond à une variable d'environnement, on supprime cette dernière. */

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

int	ft_unset(t_minish *mini, char **cmd)
{
	int i;
	int	pos;

	i = 1;
	if (args_number(cmd) < 2)
	{
		ft_putendl_fd("unset: not enough arguments", 1);
		return (ERROR);
	}
	while (i < args_number(cmd))
	{
		pos = is_in_env(mini, cmd[i]);
		if (pos != -1)
			del_env_var(mini, pos);
		i++;
	}
	return (SUCCESS);
}
