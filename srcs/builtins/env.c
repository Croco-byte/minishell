/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:39:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 13:07:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minish *mini, char **cmd)
{
	if (args_number(cmd) > 1)
	{
		ft_putendl_fd("env: option or argument not recognized", STDERR);
		return (ERROR);
	}
	display_parsed_env(mini->parsed_env, 0);
	return (SUCCESS);
}
