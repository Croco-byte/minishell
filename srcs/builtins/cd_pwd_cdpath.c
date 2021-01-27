/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_cdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:24:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:25:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
