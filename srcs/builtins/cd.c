/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:25:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_pos(t_minish *mini, char *name)
{
	int	i;

	i = 0;
	while (i < env_var_nb(mini->parsed_env))
	{
		if (ft_strcmp(mini->parsed_env[i].key, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	cd_default(t_minish *mini, char **cmd)
{
	int	home_pos;

	home_pos = env_pos(mini, "HOME");
	if (home_pos == -1)
	{
		ft_putendl_fd("minishell: cd: « HOME » not set", STDERR);
		return (1);
	}
	if (mini->parsed_env[home_pos].value[0] == '\0')
		return (0);
	if (chdir(mini->parsed_env[home_pos].value) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd[0], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(mini->parsed_env[home_pos].value, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		return (1);
	}
	return (0);
}

int	display_cd_error(char **cmd)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd[0], STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(cmd[1], STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	return (1);
}

int	cd_special_cases(t_minish *mini, char **cmd)
{
	if (args_number(cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (1);
	}
	if (args_number(cmd) < 2)
	{
		if (cd_default(mini, cmd))
			return (1);
		else
			return (0);
	}
	return (-1);
}

int	ft_cd(t_minish *mini, char **cmd)
{
	char	cwd[PATH_MAX];
	int		pass_cwd;
	int		special_cases;

	pass_cwd = 0;
	special_cases = cd_special_cases(mini, cmd);
	if (getcwd(cwd, PATH_MAX))
		pass_cwd = 1;
	if (special_cases != -1)
		return (special_cases);
	if (cd_home(mini, cmd) == 1)
		return (1);
	else if (cd_home(mini, cmd) == -1)
		return (0);
	if (cd_oldpwd(mini, cmd))
		return (1);
	if (cmd[1] && cmd[1][0] != '.' && cmd[1][0] != '/'
		&& env_pos(mini, "CDPATH") != -1)
		add_cd_path(mini, cmd);
	if (chdir(cmd[1]) == -1)
		return (display_cd_error(cmd));
	if (pass_cwd)
		update_oldpwd(mini, cwd);
	update_pwd(mini, cmd);
	return (0);
}
