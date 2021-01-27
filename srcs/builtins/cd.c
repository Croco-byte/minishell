/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 17:55:40 by user42           ###   ########.fr       */
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
	if (path[0])
		result = ft_strjoin(home_path, path + 1, 0);
	else
		result = ft_strjoin(home_path, path, 0);
	free(home_path);
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
		else if (cmd[1][1] == '\0'
			&& mini->parsed_env[env_pos(mini, "HOME")].value[0] == '\0')
			return (-1);
		cmd[1] = insert_home(mini, cmd[1]);
	}
	return (0);
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

int	cd_oldpwd(t_minish *mini, char **cmd)
{
	if (cmd[1] && cmd[1][0] == '-')
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

void	update_pwd_cd_point(t_minish *mini, char **cmd)
{
	char	*pwd;
	char	*pwd2;

	if (ft_strcmp(cmd[1], ".") == 0 || ft_strcmp(cmd[1], "./") == 0)
	{
		ft_putstr_fd("cd: error determining current directory:", STDERR);
		ft_putstr_fd(" getcwd: cannot access parent directories:", STDERR);
		ft_putendl_fd(" no such file or directory", STDERR);
		pwd = ft_strjoin("PWD=", mini->parsed_env[env_pos(mini, "PWD")].value, 0);
		pwd2 = ft_strjoin(pwd, "/.", 0);
		repl_env_var(mini, mini->parsed_env, pwd2, env_pos(mini, "PWD"));
		free(pwd);
		free(pwd2);
	}
	if (ft_strcmp(cmd[1], "..") == 0 || ft_strcmp(cmd[1], "../") == 0)
	{
		ft_putstr_fd("cd: error determining current directory:", STDERR);
		ft_putstr_fd(" getcwd: cannot access parent directories:", STDERR);
		ft_putendl_fd(" no such file or directory", STDERR);
		pwd = ft_strjoin("PWD=", mini->parsed_env[env_pos(mini, "PWD")].value, 0);
		pwd2 = ft_strjoin(pwd, "/..", 0);
		repl_env_var(mini, mini->parsed_env, pwd2, env_pos(mini, "PWD"));
		free(pwd);
		free(pwd2);
	}
}

void	update_pwd(t_minish *mini, char **cmd)
{
	char	*pwd_var;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		pwd_var = ft_strjoin("PWD=", cwd, 0);
		if (env_pos(mini, "PWD") == -1)
			add_env_var(mini, pwd_var);
		else
			repl_env_var(mini, mini->parsed_env, pwd_var, env_pos(mini, "PWD"));
		free(pwd_var);
	}
	else if (env_pos(mini, "PWD") != -1)
		update_pwd_cd_point(mini, cmd);
}

int	in_current(char *cmd)
{
	DIR		*dir;
	char	*check_current;

	check_current = ft_strjoin("./", cmd, 0);
	dir = opendir(check_current);
	if (dir)
	{
		free(check_current);
		closedir(dir);
		return (1);
	}
	free(check_current);
	closedir(dir);
	return (0);
}

int	cdpath_matches(char **path, char **cmd)
{
	int		i;
	int		found_path;
	char	*complete_dir_path;
	DIR		*dir;

	i = 0;
	found_path = 0;
	while (path[i] && !found_path)
	{
		if (path[i][ft_strlen(path[i]) - 1] == '/')
			complete_dir_path = ft_strjoin(path[i], cmd[1], 0);
		else
			complete_dir_path = ft_strjoin(path[i], cmd[1], '/');
		dir = opendir(complete_dir_path);
		if (dir)
			found_path = 1;
		else
			i++;
		closedir(dir);
		free(complete_dir_path);
	}
	if (found_path)
		return (1);
	return (0);
}

void	add_cd_path(t_minish *mini, char **cmd)
{
	int		i;
	int		found_path;
	int		path_pos;
	char	**path;

	if (in_current(cmd[1]))
		return ;
	i = 0;
	found_path = 0;
	path_pos = is_in_env(mini, "CDPATH");
	if (path_pos == -1)
		return ;
	path = ft_split(mini->parsed_env[path_pos].value, ":");
	if (cdpath_matches(path, cmd))
		prefix_path(path[i], cmd, 1);
	free_strarray(path);
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
