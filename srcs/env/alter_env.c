/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alter_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:37:04 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:37:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_var(t_minish *mini, char *var)
{
	int		i;
	int		var_nb;
	t_env	*new;

	i = 0;
	var_nb = env_var_nb(mini->parsed_env);
	new = malloc((var_nb + 2) *sizeof(t_env));
	if (!new)
		return ;
	while (i < var_nb)
	{
		new[i].has_space = mini->parsed_env[i].has_space;
		new[i].key = ft_strdup(mini->parsed_env[i].key);
		new[i].value = ft_strdup(mini->parsed_env[i].value);
		i++;
	}
	new[i].has_space = 0;
	if (char_in_str(var, '='))
		new[i].has_space = 1;
	new[i].key = ft_substr(var, 0, get_key_len(var));
	new[i++].value = get_value(var, get_key_len(var), -1, mini->parsed_env);
	new[i].key = 0;
	free_parsed_env(mini->parsed_env);
	mini->parsed_env = new;
	mini->env = update_env(mini->env, mini->parsed_env);
}

void	repl_env_var(t_minish *mini, t_env *parsed_env, char *var, int pos)
{
	int		i;
	char	*new_value;

	i = 0;
	while (i < pos)
		i++;
	new_value = get_value(var, get_key_len(var), i, parsed_env);
	if (new_value && char_in_str(var, '='))
	{
		parsed_env[i].has_space = 1;
		free(parsed_env[i].value);
		parsed_env[i].value = new_value;
	}
	else
		free(new_value);
	mini->env = update_env(mini->env, mini->parsed_env);
}
