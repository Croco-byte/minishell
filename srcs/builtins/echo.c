/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:23:20 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 11:44:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO :
	- Flag -n : le cas de "echo -nnnnn"
	- La gestion de l'escaping character \ et des characters spéciaux : par exemple "echo hey\\nyou"
*/

int	ft_echo(t_minish *mini)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (args_number(mini->args) > 1)
	{
		while (mini->args[i] != 0 && ft_strcmp(mini->args[i], "-n") == 0)
		{
			option_n = 1;
			i++;
		}
		while (mini->args[i])
		{
			ft_putstr_fd(mini->args[i], 1);
			if (mini->args[i + 1] && mini->args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option_n == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
