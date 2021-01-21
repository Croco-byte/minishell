/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:26:23 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 11:46:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shlvl(t_minish *mini, int shlvl_pos)
{
	int	current_shlvl;
	char	*new_shlvl;
	char	*new_shlvl_var;

	current_shlvl = ft_atoi(mini->parsed_env[shlvl_pos].value);
	current_shlvl++;
	new_shlvl = ft_itoa(current_shlvl);
	new_shlvl_var = ft_strjoin("SHLVL=", new_shlvl, 0);
	repl_env_var(mini, mini->parsed_env, new_shlvl_var, shlvl_pos);
	free(new_shlvl);
	free(new_shlvl_var);
}

void	increase_shell_level(t_minish *mini)
{
	int	shlvl_pos;

	shlvl_pos = is_in_env(mini, "SHLVL");
	if (shlvl_pos == -1)
		add_env_var(mini, "SHLVL=1");
	else
		increment_shlvl(mini, shlvl_pos);
}
