/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 17:20:17 by user42           ###   ########.fr       */
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

char	*insert_home(t_minish *mini, char *path)
{
	char	*result;
	int		home_pos;
	char	*home_path;

	home_pos = env_pos(mini, "HOME");
	home_path = ft_strdup(mini->parsed_env[home_pos].value);
	result = ft_strjoin(home_path, path + 1, 0);
	free(home_path);
	free(path);
	return (result);
}

char	*insert_oldpwd(t_minish *mini, char *path)
{
	char	*result;
	int		oldpwd_pos;
	char	*oldpwd_path;

	oldpwd_pos = env_pos(mini, "OLDPWD");
	oldpwd_path = ft_strdup(mini->parsed_env[oldpwd_pos].value);
	result = ft_strjoin(oldpwd_path, path + 1, 0);
	free(oldpwd_path);
	free(path);
	return (result);
}

int	cd_home(t_minish *mini, char **cmd)
{
	if (cmd[1][0] == '~')
	{
		if (env_pos(mini, "HOME") == -1)
		{
			ft_putendl_fd("minishell: cd: « HOME » not set", STDERR);
			return (1);
		}
		cmd[1] = insert_home(mini, cmd[1]);
	}
	return (0);
}

int	cd_oldpwd(t_minish *mini, char **cmd)
{
	if (cmd[1][0] == '-')
	{
		if (cmd[1][1] != '\0')
		{
			ft_putstr_fd("minishell: cd: ", STDERR);
			ft_putstr_fd(cmd[1], STDERR);
			ft_putendl_fd(" : invalid option", STDERR);
			return (1);
		}
		if (env_pos(mini, "OLDPWD") == -1)
		{
			ft_putendl_fd("minishell: cd: « OLDPWD » not set", STDERR);
			return (1);
		}
		cmd[1] = insert_oldpwd(mini, cmd[1]);
	}
	return (0);
}

void	update_oldpwd(t_minish *mini, char *cwd)
{
	char	*oldpwd_var;

	oldpwd_var = ft_strjoin("OLDPWD=", cwd, 0);
	if (env_pos(mini, "OLDPWD") == -1)
		add_env_var(mini, oldpwd_var);
	else
		repl_env_var(mini, mini->parsed_env, oldpwd_var, env_pos(mini, "OLDPWD"));
	free(oldpwd_var);
}

int	ft_cd(t_minish *mini, char **cmd)
{
	char	cwd[PATH_MAX];
	int		pass_cwd;
	
	pass_cwd = 0;
	if (getcwd(cwd, PATH_MAX))
		pass_cwd = 1;
	if (args_number(cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (1);
	}
	if (cd_home(mini, cmd))
		return (1);
	if (cd_oldpwd(mini, cmd))
		return (1);
	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd[0], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		return (1);
	}
	if (pass_cwd)
		update_oldpwd(mini, cwd);
	return (0);
}
