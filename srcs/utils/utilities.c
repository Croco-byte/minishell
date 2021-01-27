/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:10:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:51:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt(void)
{
	if (g_status.code == 0)
		ft_putstr_fd("\033[1;32m🐊 minishell ▸ \033[0m", STDERR);
	else
		ft_putstr_fd("\033[1;31m🐊 minishell ▸ \033[0m", STDERR);
}

int	is_builtin(char *prog_name)
{
	if (!ft_strcmp(prog_name, "echo") || !ft_strcmp(prog_name, "cd")
		|| !ft_strcmp(prog_name, "pwd") || !ft_strcmp(prog_name, "export")
		|| !ft_strcmp(prog_name, "unset") || !ft_strcmp(prog_name, "env")
		|| !ft_strcmp(prog_name, "exit"))
		return (1);
	return (0);
}

int	args_number(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

int	env_var_nb(t_env *parsed_env)
{
	int	i;

	i = 0;
	if (!parsed_env)
		return (0);
	while (parsed_env[i].key)
		i++;
	return (i);
}

int	is_escaped(char *str, int index)
{
	int	i;
	int	backslash_count;

	i = index;
	if (i == 0)
		return (0);
	i--;
	backslash_count = 0;
	while (i >= 0 && str[i] == '\\')
	{
		backslash_count++;
		i--;
	}
	if (backslash_count % 2 == 0)
		return (0);
	else
		return (1);
}
