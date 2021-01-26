/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:48:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 15:28:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_in_dir(char *bin, DIR *dir)
{
	struct dirent	*file;

	if (!dir)
		return (0);
	file = readdir(dir);
	while (file)
	{
		if (ft_strcmp(file->d_name, bin) == 0)
			return (1);
		file = readdir(dir);
	}
	return (0);
}

void	prefix_path(char *path, char **cmd, int i)
{
	char	*new;

	if (path[ft_strlen(path) - 1] == '/')
		new = ft_strjoin(path, cmd[i], 0);
	else
		new = ft_strjoin(path, cmd[i], '/');
	free(cmd[i]);
	cmd[i] = new;
}

void	add_path(t_minish *mini, char **cmd)
{
	int		i;
	int		found_path;
	int		path_pos;
	char	**path;
	DIR		*dir;

	i = 0;
	found_path = 0;
	path_pos = is_in_env(mini, "PATH");
	if (path_pos == -1)
		return ;
	path = ft_split(mini->parsed_env[path_pos].value, ":");
	while (path[i] && !found_path)
	{
		dir = opendir(path[i]);
		if (bin_in_dir(cmd[0], dir))
			found_path = 1;
		else
			i++;
		closedir(dir);
	}
	if (found_path)
		prefix_path(path[i], cmd, 0);
	free_strarray(path);
}

void	display_bin_error(t_minish *mini, char *path, int fd, DIR *folder)
{
	int	path_exists;

	path_exists = is_in_env(mini, "PATH");
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == 0 && path_exists != -1
		&& mini->parsed_env[path_exists].value[0] != '\0')
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == 0)
		ft_putendl_fd(": no such file or directory", STDERR);
	else if (fd == -1 && folder != 0)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == 0)
		ft_putendl_fd(": permission denied", STDERR);
}

int	handle_errors(t_minish *mini, char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ret = is_in_env(mini, "PATH");
	display_bin_error(mini, path, fd, folder);
	if ((ft_strchr(path, '/') == 0 && ret != -1
			&& mini->parsed_env[ret].value[0] != '\0')
		|| (fd == -1 && folder == 0))
		ret = 127;
	else if ((fd == -1 && folder != 0) || (fd != -1 && folder == 0))
		ret = 126;
	else
		ret = 1;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	exec_bin(t_minish *mini, char **cmd)
{
	int	ret;

	ret = 0;
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
		add_path(mini, cmd);
	g_status.pid = fork();
	if (g_status.pid == 0)
	{
		if (execve(cmd[0], cmd, mini->env) == -1)
			ret = handle_errors(mini, cmd[0]);
		free_token(mini->start);
		exit(ret);
	}
	else if (g_status.pid < 0)
		ft_putendl_fd("Error forking", 1);
	else
		waitpid(g_status.pid, &ret, 0);
	if (!WIFSIGNALED(ret))
		g_status.code = WEXITSTATUS(ret);
	return (ret);
}
