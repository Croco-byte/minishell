/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:39:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 15:41:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Builtin "env" qui ne fait qu'afficher l'environnement sous la forme clé=valeur. */

int	ft_env(t_minish *mini, char **cmd)
{
	if (args_number(cmd) > 1)
	{
		ft_putendl_fd("env: option or argument not recognized", 1);
		return (ERROR);
	}
	display_parsed_env(mini->parsed_env, 1);
	return (SUCCESS);
}
