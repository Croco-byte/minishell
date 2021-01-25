/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:23:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 11:45:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_echo_flag(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	if (str[i] == '\0')
		return (0);
	while(str[i] && str[i] == c)
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (args_number(cmd) > 1)
	{
		while (cmd[i] != 0 && is_echo_flag(cmd[i], 'n'))
		{
			option_n = 1;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], STDOUT);
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (option_n == 0)
		write(1, "\n", 1);
	return (0);
}
