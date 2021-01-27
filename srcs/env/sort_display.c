/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:31:31 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:32:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_parsed_env(t_env *parsed_env)
{
	int		i;
	int		j;
	int		var_nb;
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

int	display_sorted(t_minish *mini)
{
	t_env	*copy;

	copy = copy_parsed_env(mini->parsed_env);
	sort_parsed_env(copy);
	display_parsed_env(copy, 1);
	free_parsed_env(copy);
	return (0);
}
