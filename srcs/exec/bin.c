/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:48:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:12:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
