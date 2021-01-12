/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:59:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 15:21:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ces fonctions sont relatives au builtin "export". S'il n'y a aucun argument, ce builtin affiche les variables d'environnement triées par ordre alphabétique.
S'il y a un ou plusieurs arguments, on vérifie s'ils sont des variables d'environnement valides. Pour chacun de ces arguments valides :
 > S'il existe déjà dans l'environnement, on remplace la variable dans l'environnement.
 > S'il n'existe pas dans l'environnement, on l'ajoute. */

void	display_sorted(t_minish *mini)
{
	t_env	*copy;

	copy = copy_parsed_env(mini->parsed_env);
	sort_parsed_env(copy);
	display_parsed_env(copy, EXPORT_DISP);
	free_parsed_env(copy);
}

int		is_env_var(char *var)
{
	int	i;
	char	*key;
	char	*value;

	key = ft_substr(var, 0, get_key_len(var));
	value = get_value(var, get_key_len(var));
	i = 0;
	if (ft_isdigit(key[0]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	free(key);
	free(value);
	return (1);
}

void	add_env_var(t_minish *mini, char *var)
{
	int	i;
	int	var_nb;
	t_env	*new;

	i = 0;
	var_nb = env_var_nb(mini->parsed_env);
	new = malloc((var_nb + 2) * sizeof(t_env));
	if (!new)
		return ;
	while (i < var_nb)
	{
		new[i].key = ft_strdup(mini->parsed_env[i].key);
		new[i].value = ft_strdup(mini->parsed_env[i].value);
		i++;
	}
	new[i].key = ft_substr(var, 0, get_key_len(var));
	new[i++].value = get_value(var, get_key_len(var));
	new[i].key = 0;
	free_parsed_env(mini->parsed_env);
	mini->parsed_env = new;
	mini->env = update_env(mini->env, mini->parsed_env);
}

void	repl_env_var(t_minish *mini, t_env *parsed_env, char *var, int pos)
{
	int	i;
	char	*new_key;
	char	*new_value;

	new_key = ft_substr(var, 0, get_key_len(var));
	new_value = get_value(var, get_key_len(var));
	i = 0;
	while (i < pos)
		i++;
	free(parsed_env[i].key);
	parsed_env[i].key = new_key;
	if (new_value[0] != '\0')
	{
		free(parsed_env[i].value);
		parsed_env[i].value = new_value;
	}
	else
		free(new_value);
	mini->env = update_env(mini->env, mini->parsed_env);
}

int	ft_export(t_minish *mini)
{
	int	i;

	i = 1;
	if (args_number(mini->args) <= 1)
	{
		display_sorted(mini);
		return (SUCCESS);
	}
	while (i < args_number(mini->args))
	{
		if (!is_env_var(mini->args[i]))
			ft_printf("export: not valid in this context: %s\n", mini->args[i]);
		else
			if (is_in_env(mini, mini->args[i]) != -1)
				repl_env_var(mini, mini->parsed_env, mini->args[i], is_in_env(mini, mini->args[i]));
			else
				add_env_var(mini, mini->args[i]);
		i++;
	}
	return (SUCCESS);
}

