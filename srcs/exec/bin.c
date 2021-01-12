/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:48:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 17:48:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* L'ensemble de ces fonctions est utilisé pour exécuter un binaire, passé en première position d'une commande. Si ce binaire commence par '/' ou '.', on ne le cherche
pas dans la variable d'environnement PATH, car l'utilisateur a donné un chemin absolu. Sinon, on cherche dans tous les dossiers présents dans la variable PATH, voir
si on trouve notre binaire. Si oui, on ajoute le PATH.

Une fois que c'est fait, on appelle la fonction fork(), qui spawn un nouveau process. Cette fonction renvoie un nombre positif quelconque au processus parent (minishell),
et 0 au processus enfant (le programme exécuté). Le processus enfant exécute la commande qui lui est passée par execve. Le processus parent attend que le processus
enfant ait fini d'exécuter la commande pour faire quoi que ce soit (waitpid).*/

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

int	handle_errors(t_minish *mini, char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ret = is_in_env(mini, "PATH");
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == 0 && ret != -1 && mini->parsed_env[ret].value[0] != '\0')
		ft_putendl_fd(": command not found", STDERR);											// --> On a pas trouvé la commande dans les builtins, ni dans la variable d'environnement PATH, qui existe et n'est pas vide.
	else if (fd == -1 && folder == 0)
		ft_putendl_fd(": no such file or directory", STDERR);
	else if (fd == -1 && folder != 0)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == 0)
		ft_putendl_fd(": permission denied", STDERR);
	if ((ft_strchr(path, '/') == 0 && ret != -1 && mini->parsed_env[ret].value[0] != '\0') || (fd == -1 && folder == 0))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return (ret);
}

int	exec_bin(t_minish *mini)
{
	int ret;

	ret = 0;
	if (mini->args[0][0] != '/' && mini->args[0][0] != '.')
		add_path(mini);
	status.pid = fork();
	if (status.pid == 0)
	{
		if (execve(mini->args[0], mini->args, mini->env) == -1)
			ret = handle_errors(mini, mini->args[0]);
		exit(ret);
	}
	else if (status.pid < 0)
		ft_putendl_fd("Error forking", 1);
	else
		waitpid(status.pid, &ret, 0);
	if (!WIFSIGNALED(ret))
		status.code = WEXITSTATUS(ret);
	return (status.code);
}
