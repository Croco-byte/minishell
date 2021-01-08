/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:17:59 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 15:24:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*get_value(char *var, int pos)
{
	if (!var[pos])
		return (ft_strdup("\0"));
	else
		pos++;
	if (!var[pos])
		return (ft_strdup("\0"));
	else
		return (ft_strdup(var + pos));
}

void	parse_env(t_minish *mini, char **env)
{
	int	i;
	int	arg_nb;
	int	key_len;

	arg_nb = args_number(env);
	i = 0;
	mini->parsed_env = malloc((arg_nb + 1) * sizeof(t_env));
	if (!mini->parsed_env)
		return ;
	while (env[i])
	{
		key_len = get_key_len(env[i]);
		mini->parsed_env[i].key = ft_substr(env[i], 0, key_len);
		mini->parsed_env[i].value = get_value(env[i], key_len);
		i++;
	}
	mini->parsed_env[i].key = 0;
	mini->parsed_env[i].value = 0; 
}

char	**update_env(char **env, t_env *parsed_env)
{
	int	i;
	int	var_nb;
	char	**result;

	i = 0;
	var_nb = env_var_nb(parsed_env);
	free_strarray(env);
	result = malloc((var_nb + 1) * sizeof(char *));
	while (i < var_nb)
	{
		result[i] = ft_strjoin(parsed_env[i].key, parsed_env[i].value, '=');
		i++;
	}
	result[i] = 0;
	return (result);
}
