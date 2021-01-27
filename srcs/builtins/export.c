/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:59:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:36:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_export_error(char **cmd, int i)
{
	ft_putstr_fd("minishell: export: not valid in this context: ", STDERR);
	ft_putendl_fd(cmd[i], STDERR);
	return (1);
}

int	ft_export(t_minish *mini, char **cmd)
{
	int	i;
	int	error_happened;

	i = 1;
	error_happened = 0;
	if (args_number(cmd) <= 1)
		return (display_sorted(mini));
	while (i < args_number(cmd))
	{
		if (!is_env_var(cmd[i]) || cmd[i][0] == '\0')
			error_happened = display_export_error(cmd, i);
		else
		{
			if (is_in_env(mini, cmd[i]) != -1)
				repl_env_var(mini, mini->parsed_env, cmd[i],
					is_in_env(mini, cmd[i]));
			else
				add_env_var(mini, cmd[i]);
		}
		i++;
	}
	return (error_happened);
}
