/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:36:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 16:44:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Builtin "exit" qui fait appel à une fonction qui free nos variables qui ont été malloc, avant de quitter proprement */

#include "minishell.h"

void	ft_exit(t_minish *mini, char **cmd)
{
	free_strarray(cmd);
	clean_exit(mini);
}
