/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:46:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:47:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && is_escaped(line, i) && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

int	sep_after_backslashes(char *line, int i)
{
	while (line[i] && line[i] == '\\')
		i++;
	if (line[i] && (line[i] == '>' || line[i] == ';' || line[i] == '|'
			|| (line[i] == '>' && line[i + 1] && line[i + 1] == '>')))
		return (1);
	return (0);
}

int	nb_of_backslashes(char *line, int i)
{
	int	count;

	count = 0;
	while (line[i] && line[i] == '\\')
	{
		i++;
		count++;
	}
	return (count);
}

int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && sep_after_backslashes(line, i)
		&& nb_of_backslashes(line, i) % 2 != 0)
		return (1);
	return (0);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && is_escaped(line, i))
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}
