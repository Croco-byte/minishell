/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:22:31 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 15:47:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete(char *arg, int begin)
{
	int		var_width;
	char	*result;

	var_width = var_end_dist(arg, begin);
	result = malloc(((ft_strlen(arg) - var_width) + 1) * sizeof(char));
	if (!result)
		return (0);
	replace_str(result, arg, 0, begin);
	return (result);
}

char	*replace_err_code(char *arg, int begin)
{
	int i;
	int j;
	char	*err_code;
	char	*result;

	i = 0;
	j = 0;
	err_code = ft_itoa(status.code);
	result = malloc((ft_strlen(arg) + (ft_strlen(err_code) - 1) + 1) * sizeof(char));
	if (!result)
		return (0);
	replace_code(result, arg, err_code, begin);
	free(err_code);
	return (result);
}

char	*replace_var(t_minish *mini, char *arg, int begin, int env_index)
{
	int	len_diff;
	char	*result;

	len_diff = ft_strlen(mini->parsed_env[env_index].value) - var_end_dist(arg, begin);
	result = malloc(((ft_strlen(arg) + len_diff) + 2) * sizeof(char));
	if (!result)
		return (0);
	replace_str(result, arg, mini->parsed_env[env_index].value, begin);
	return (result);
}

char	*replace_or_delete(t_minish *mini, char *arg)
{
	int	i;
	char	*result;

	i = 0;
	result = 0;
	while (arg[i])
	{
		if (arg[i] == -36 && quotes(arg, i) != 2)
		{
			if (arg[i + 1] == '?')
				result = replace_err_code(arg, i);
			else if (!ft_isalnum(arg[i + 1]) && arg[i + 1] != '_')
				arg[i] = '$';
			else if (exp_in_env(mini, arg, i + 1) != -1)
				result = replace_var(mini, arg, i, exp_in_env(mini, arg, i + 1));
			else
				result = delete(arg, i);
			break ;
		}
		i++;
	}
	return (result);
}

char	*expand(t_minish *mini, char *arg)
{
	char *result;

	result = replace_or_delete(mini, arg);
	if (!result)
		result = ft_strdup(arg);
	if (result && char_in_str(result, -36))
		result = expand(mini, result);
	free(arg);
	return (result);
}
