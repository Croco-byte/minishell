/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:10:47 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 13:20:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Temporary function to display line parsing, to be removed later */
void	display_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_printf("args[%i] : |%s|\n", i, args[i]);
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