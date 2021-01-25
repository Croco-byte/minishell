/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:14:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 12:38:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ces fonctions servent à la manipulation de l'environnement dans sa version parsée (vérifier qu'une variable passée à une commande est bien dans l'environnement,
trier l'environnement pour l'afficher par ordre alphabétique, afficher l'environnement.) */

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int		is_in_env(t_minish *mini, char *var)
{
	int	i;
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
	int	i;
	int	var_nb;
	t_env	*copy;

	i = 0;
	var_nb = env_var_nb(parsed_env);
	copy = malloc((var_nb + 1) * sizeof(t_env));
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

void	sort_parsed_env(t_env *parsed_env)
{
	int	i;
	int	j;
	int	var_nb;
	t_env	temp;

	i = 0;
	var_nb = env_var_nb(parsed_env);
	while (i < var_nb)
	{
		j = i + 1;
		while (j < var_nb)
		{
			if (ft_strcmp(parsed_env[i].key, parsed_env[j].key) > 0)
			{
				temp = parsed_env[i];
				parsed_env[i] = parsed_env[j];
				parsed_env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	display_non_empty(t_env *parsed_env, int which, int i)
{
	if (which)
		ft_putstr_fd("declare -x ", STDOUT);
	ft_putstr_fd(parsed_env[i].key, STDOUT);
	ft_putchar_fd('=', STDOUT);
	if (which)
		ft_putchar_fd('"', STDOUT);
	ft_putstr_fd(parsed_env[i].value, STDOUT);
	if (which)
		ft_putchar_fd('"', STDOUT);
	ft_putchar_fd('\n', STDOUT);
}

void	display_empty(t_env *parsed_env, int which, int i)
{
	if (which)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(parsed_env[i].key, STDOUT);
		if (parsed_env[i].has_space)
			ft_putstr_fd("=\"\"", STDOUT);
		ft_putchar_fd('\n', STDOUT);
	}
	else if (parsed_env[i].has_space)
	{
		ft_putstr_fd(parsed_env[i].key, STDOUT);
		ft_putendl_fd("=", STDOUT);
	}
}

void	display_parsed_env(t_env *parsed_env, int which)
{
	int	i;

	i = 0;
	while (parsed_env[i].key)
	{
		if (parsed_env[i].value[0] != '\0')
			display_non_empty(parsed_env, which, i);
		else
			display_empty(parsed_env, which, i);
		i++;
	}
}
