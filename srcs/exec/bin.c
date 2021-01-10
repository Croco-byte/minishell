/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:48:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/09 13:09:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bin_in_dir(char *bin, DIR *dir)
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

void	prefix_path(char *path, t_minish *mini)
{
	char	*new;

	if (path[ft_strlen(path) - 1] == '/')
		new = ft_strjoin(path, mini->args[0], 0);
	else
		new = ft_strjoin(path, mini->args[0], '/');
	free(mini->args[0]);
	mini->args[0] = new;
}

void	add_path(t_minish *mini)
{
	int	i;
	int	found_path;
	int	path_pos;
	char	**path;
	DIR	*dir;

	i = 0;
	found_path = 0;
	path_pos = is_in_env(mini, "PATH");
	if (path_pos == -1)
		return ;
	path = ft_split(mini->parsed_env[path_pos].value, ":");
	while (path[i] && !found_path)
	{
		dir = opendir(path[i]);
		if (bin_in_dir(mini->args[0], dir))
			found_path = 1;
		else
			i++;
		closedir(dir);
	}
	if (found_path)
		prefix_path(path[i], mini);
	free_strarray(path);
}

void	exec_bin(t_minish *mini)
{
	int status;

	if (mini->args[0][0] != '/' && mini->args[0][0] != '.')
		add_path(mini);
	sig.pid = fork();
	if (sig.pid == 0)
	{
		if (execve(mini->args[0], mini->args, mini->env) == -1)
		{
			ft_printf("%s : ", mini->args[0]);
			ft_putendl_fd(strerror(errno), 1);
		}
		exit(ERROR);
	}
	else if (sig.pid < 0)
		ft_putendl_fd("Error forking", 1);
	else
	{
		waitpid(sig.pid, &status, 0);
	}
}
