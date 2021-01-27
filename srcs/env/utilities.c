/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:14:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:34:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	is_env_var(char *var)
{
	int	i;

	i = 0;
	if (var && (ft_isdigit(var[0]) || var[0] == '='))
		return (0);
	while (var && var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' || var[i] == '='
		|| (var[i] == '+' && var[i + 1] && var[i + 1] == '='))
		return (1);
	return (0);
}

int	is_in_env(t_minish *mini, char *var)
{
	int		i;
	char	*key;

	key = ft_substr(var, 0, get_key_len(var));
	i = 0;
	while (i < env_var_nb(mini->parsed_env))
	{
		if (ft_strcmp(mini->parsed_env[i].key, key) == 0)
		{
			free(key);
			return (i);
		}
		i++;
	}
	free(key);
	return (-1);
}

t_env	*copy_parsed_env(t_env *parsed_env)
{
	int		i;
	int		var_nb;
	t_env	*copy;

	i = 0;
	var_nb = env_var_nb(parsed_env);
	copy = malloc((var_nb + 1) *sizeof(t_env));
	if (!copy)
		return (0);
	while (i < var_nb)
	{
		copy[i].has_space = parsed_env[i].has_space;
		copy[i].key = ft_strdup(parsed_env[i].key);
		copy[i].value = ft_strdup(parsed_env[i].value);
		i++;
	}
	copy[i].key = 0;
	return (copy);
}
