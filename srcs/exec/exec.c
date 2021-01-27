/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:09:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 14:15:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_from_tokens(t_token *start)
{
	int		i;
	t_token	*token;
	char	**tab;

	if (!start)
		return (0);
	i = 0;
	token = start;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc((i + 1) *sizeof(char *));
	if (!tab)
		return (0);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i++] = ft_strdup(token->str);
		token = token->next;
	}
	tab[i] = 0;
	return (tab);
}

void	handle_expansions(t_minish *mini, char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expand(mini, cmd[i]);
		i++;
	}
}

void	handle_quotes_strip(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = strip_quotes(cmd[i]);
		i++;
	}
}

void	exec_cmd(t_minish *mini, t_token *token)
{
	int		i;
	char	**cmd;

	i = 0;
	if (mini->charge == 0)
		return ;
	cmd = cmd_from_tokens(token);
	handle_expansions(mini, cmd);
	while (cmd && cmd[i] && cmd[i + 1])
	{
		if (cmd[i][0] == '\0')
			cmd = delete_arg(cmd, i);
		i++;
	}
	if (cmd && cmd[i] && cmd[i][0] == '\0')
		cmd = delete_arg(cmd, i);
	handle_quotes_strip(cmd);
	if (cmd && cmd[0] && is_builtin(cmd[0]))
		g_status.code = exec_builtin(mini, cmd);
	else if (cmd[0])
		exec_bin(mini, cmd);
	free_strarray(cmd);
	mini->charge = 0;
}
