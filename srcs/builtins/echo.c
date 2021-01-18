/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:23:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 15:45:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO :
	- Flag -n : le cas de "echo -nnnnn"
	- La gestion de l'escaping character \ et des characters spéciaux : par exemple "echo hey\\nyou"
*/

int	ft_echo(char **cmd)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (args_number(cmd) > 1)
	{
		while (cmd[i] != 0 && ft_strcmp(cmd[i], "-n") == 0)
		{
			option_n = 1;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] && cmd[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option_n == 0)
		write(1, "\n", 1);
	return (0);
}
