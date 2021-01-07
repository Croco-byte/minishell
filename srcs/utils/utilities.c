/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:10:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 17:58:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_strarray(char **strarray)
{
	int i;

	i = 0;
	while (strarray[i])
	{
		ft_putendl_fd(strarray[i], 1);
		i++;
	}
}

char	**copy_strarray(char **src)
{
	int	i;
	int	arg_nb;
	char	**copy;

	i = 0;
	arg_nb = args_number(src);
	copy = malloc((arg_nb + 1) * sizeof(char *));
	if (!copy)
		return (0);
	while (i < arg_nb)
	{
		copy[i] = ft_strdup(src[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int	ft_strcmp_keys(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '=')
		return (0 - (unsigned char)s2[i]);
	else if (s2[i] == '=')
		return ((unsigned char)s1[i] - 0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_strarray(char **to_sort)
{
	int	i;
	int	j;
	int	arg_nb;
	char	*temp;

	i = 0;
	arg_nb = args_number(to_sort);
	while (i < arg_nb)
	{
		j = i + 1;
		while (j < arg_nb)
		{
			if (ft_strcmp_keys(to_sort[i], to_sort[j]) > 0)
			{
				temp = to_sort[i];
				to_sort[i] = to_sort[j];
				to_sort[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_prompt(void)
{
	ft_putstr_fd("\033[1;32m🐊 minishell ▸ \033[0m", 1);
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
	int i;

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
