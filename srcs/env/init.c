/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:17:59 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 14:15:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Lorsqu'on lance le programme ./minishell, l'environnement de la shell actuelle lui est passé sous la forme d'un char **env, contenant des chaînes de caractères du
format "clé=valeur". Quand on reçoit ce char **, la première chose qu'on fait, c'est qu'on le parse. En effet, t_minish *mini a un tableau de structures t_env *parsed_env, composée
 de deux chaînes de caractères (key et value). Chaque structure correspond à une variable d'environnement, et stocke dans sa variable "key" la clé, et dans sa variable
 "value" la valeur de la variable d'environnement.
 Par exemple si la première variable d'environnement est "VAR1=hello", la première structure du tableau aura pour key "VAR1" et pour value "hello". Un tel découpage permet
 de gérer les variables d'environnement de manière plus précise (pour les trier, en retirer, en ajouter...). A chaque fois que l'environnement est modifié, c'est à partir
 de ce tableau de structures.
 
 Cependant, nous avons également besoin d'un environnement sous la forme d'un char ** (pour la fonction execve qui exécute les binaries). Donc t_minish *mini a
 également une variable char **env, qui n'est que la version char ** de notre tableau de structure. A chaque fois que notre tableau de structure est modifié,
 char **env est mis à jour pour refléter les changements. */

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
