/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:06:03 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:08:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_quotes_len(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (is_ignored_char(cmd, i))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*strip_quotes(char *cmd)
{
	int		i;
	int		j;
	char	*result;

	result = malloc((no_quotes_len(cmd) + 1) *sizeof(char));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (is_ignored_char(cmd, i))
			i++;
		else
			result[j++] = cmd[i++];
	}
	result[j] = '\0';
	free(cmd);
	return (result);
}

char	**delete_arg(char **cmd, int i)
{
	char	**result;
	int		j;

	result = malloc(args_number(cmd) * sizeof(char *));
	if (!result)
		return (0);
	j = 0;
	while (j < i)
	{
		result[j] = ft_strdup(cmd[j]);
		j++;
	}
	while (cmd[j + 1])
	{
		result[j] = ft_strdup(cmd[j + 1]);
		j++;
	}
	result[j] = 0;
	free_strarray(cmd);
	return (result);
}
