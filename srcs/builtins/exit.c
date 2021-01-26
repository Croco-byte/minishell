/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:36:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 15:26:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_nbr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (i < (int)ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	nb_too_big(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '-')
		return (0);
	if ((int)ft_strlen(nb) < 19)
		return (0);
	if ((int)ft_strlen(nb) > 19)
		return (1);
	if (nb[i + 1] > '2' || nb[i + 2] > '2' || nb[i + 3] > '3' || nb[i + 4] > '3'
		|| nb[i + 5] > '7' || nb[i + 6] > '2' || nb[i + 7] > '0'
		|| nb[i + 8] > '3' || nb[i + 9] > '6' || nb[i + 10] > '8'
		|| nb[i + 11] > '5' || nb[i + 12] > '4' || nb[i + 13] > '7'
		|| nb[i + 14] > '7' || nb[i + 15] > '5' || nb[i + 16] > '8'
		|| nb[i + 17] > '0' || nb[i + 18] > '7')
		return (1);
	return (0);
}

int	nb_too_small(char *nb)
{
	int	i;

	i = 1;
	if (nb[0] != '-')
		return (0);
	if ((int)ft_strlen(nb) < 20)
		return (0);
	if ((int)ft_strlen(nb) > 20)
		return (1);
	if (nb[i + 1] > '2' || nb[i + 2] > '2' || nb[i + 3] > '3' || nb[i + 4] > '3'
		|| nb[i + 5] > '7' || nb[i + 6] > '2' || nb[i + 7] > '0'
		|| nb[i + 8] > '3' || nb[i + 9] > '6' || nb[i + 10] > '8'
		|| nb[i + 11] > '5' || nb[i + 12] > '4' || nb[i + 13] > '7'
		|| nb[i + 14] > '7' || nb[i + 15] > '5' || nb[i + 16] > '8'
		|| nb[i + 17] > '0' || nb[i + 18] > '8')
		return (1);
	return (0);
}

void	error_and_exit(t_minish *mini, char **cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(cmd[1], STDERR);
	ft_putendl_fd(" numeric argument required", STDERR);
	g_status.code = 2;
	free_strarray(cmd);
	clean_exit(mini);
}

int	ft_exit(t_minish *mini, char **cmd)
{
	int	ret;

	if (args_number(cmd) > 1)
	{
		if (!str_is_nbr(cmd[1]) || nb_too_big(cmd[1]) || nb_too_small(cmd[1]))
			error_and_exit(mini, cmd);
		else if (args_number(cmd) > 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR);
			return (1);
		}
		else
		{
			ret = ft_atoi(cmd[1]);
			while (ret > 2147483647 || ret < -2147483648)
				ret /= 2147483647;
			g_status.code = ft_atoi(cmd[1]);
		}
	}
	free_strarray(cmd);
	clean_exit(mini);
	return (0);
}
