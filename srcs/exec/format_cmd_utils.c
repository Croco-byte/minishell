/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:07:04 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:08:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	backslash(char *cmd, int i)
{
	if (cmd[i] == '\\' && quotes(cmd, i) != 1
		&& quotes(cmd, i) != 2 && !is_escaped(cmd, i))
		return (1);
	return (0);
}

int	backslash_in_dquotes(char *cmd, int i)
{
	if (cmd[i] == '\\' && quotes(cmd, i) == 1 && cmd[i + 1]
		&& (cmd[i + 1] == '\\' || cmd[i + 1] == '\"' || cmd[i + 1] == '$')
		&& !(is_escaped(cmd, i)))
		return (1);
	return (0);
}

int	backslash_in_squotes(char *cmd, int i)
{
	if (cmd[i] == '\\' && quotes(cmd, i) == 2 && cmd[i + 1]
		&& (cmd[i + 1] == '\\' || cmd[i + 1] == '\'' || cmd[i + 1] == '$')
		&& !(is_escaped(cmd, i)))
		return (1);
	return (0);
}

int	is_ignored_char(char *cmd, int i)
{
	if (cmd[i] == '\"' && quotes(cmd, i) != 2 && !is_escaped(cmd, i))
		return (1);
	else if (cmd[i] == '\'' && quotes(cmd, i) != 1 && !is_escaped(cmd, i))
		return (1);
	else if (backslash(cmd, i))
		return (1);
	else if (backslash_in_dquotes(cmd, i))
		return (1);
	else if (backslash_in_squotes(cmd, i))
		return (1);
	return (0);
}
