/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:12:23 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:12:51 by user42           ###   ########.fr       */
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
