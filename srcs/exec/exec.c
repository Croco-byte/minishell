/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:09:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 16:44:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_minish *mini)
{
	if (mini->args[0] && is_builtin(mini->args[0]))
		exec_builtin(mini);
	else if (mini->args[0])
		exec_bin(mini);
}
