/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:59:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 13:32:54 by user42           ###   ########.fr       */
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
	display_parsed_env(copy, 1);
	free_parsed_env(copy);
}

int		is_env_var(char *var)
{
	int	i;

	i = 0;
	if (var && (ft_isdigit(var[0]) || var[0] == '='))
		return (0);
	while(var && var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' || var[i] == '=' || (var[i] == '+' && var[i + 1] && var[i + 1] == '='))
		return (1);
	return (0);
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
	int	i;
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

int	ft_export(t_minish *mini, char **cmd)
{
	int	i;
	int	error_happened;

	i = 1;
	error_happened = 0;
	if (args_number(cmd) <= 1)
	{
		display_sorted(mini);
		return (0);
	}
	while (i < args_number(cmd))
	{
		if (!is_env_var(cmd[i]) || cmd[i][0] == '\0')
		{
			ft_putstr_fd("minishell: export: not valid in this context: ", STDERR);
			ft_putendl_fd(cmd[i], STDERR);
			error_happened = 1;
		}
		else
			if (is_in_env(mini, cmd[i]) != -1)
				repl_env_var(mini, mini->parsed_env, cmd[i], is_in_env(mini, cmd[i]));
			else
				add_env_var(mini, cmd[i]);
		i++;
	}
	return (error_happened);
}

