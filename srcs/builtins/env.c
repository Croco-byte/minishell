/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:39:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/08 11:50:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minish *mini)
{
	if (args_number(mini->args) > 1)
	{
		ft_putendl_fd("env: option or argument not recognized", 1);
		return (ERROR);
	}
	display_parsed_env(mini->parsed_env, ENV_DISP);
	return (SUCCESS);
}