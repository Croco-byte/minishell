/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:21:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 16:50:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	var_end_dist(char *str, int index)
{
	int	i;

	i = 0;
	if (str[index] == -36)
	{
		i++;
		index++;
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
	{
		index++;
		i++;
	}
	return (i);
}

int	exp_in_env(t_minish *mini, char *arg, int begin)
{
	int		i;
	char	*key;

	key = ft_substr(arg, begin, var_end_dist(arg, begin));
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

void	replace_str(char *result, char *src, char *to_insert, int index)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (i++ < index - 1)
		result[i] = src[i];
	if (to_insert)
	{
		while (j < (int)ft_strlen(to_insert))
			result[i++] = to_insert[j++];
	}
	j = index + var_end_dist(src, index);
	while (src[j])
		result[i++] = src[j++];
	result[i] = '\0';
}

void	replace_code(char *result, char *src, char *to_insert, int index)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (i++ < index - 1)
		result[i] = src[i];
	if (to_insert)
	{
		while (j < (int)ft_strlen(to_insert))
			result[i++] = to_insert[j++];
	}
	j = index + 2;
	while (src[j])
		result[i++] = src[j++];
	result[i] = '\0';
}
