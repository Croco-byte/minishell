/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:09:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 15:51:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si le premier argument de la commande est un builtin, on envoie la commande aux fonctions builtins. Sinon, c'est un binary, on l'envoie vers la fonction qui
gère l'exécution des binaries. */

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
	tab = malloc((i + 1) * sizeof(char *));
	if (!tab)
		return (0);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	tab[i] = 0;
	return (tab);
}


void	exec_cmd(t_minish *mini, t_token *token)
{
	int	i;
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = cmd_from_tokens(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expand(mini, cmd[i]);
		i++;
	}
	if (cmd[0] && is_builtin(cmd[0]))
		status.code = exec_builtin(mini, cmd);
	else if (cmd[0])
		status.code = exec_bin(mini, cmd);
	free_strarray(cmd);
	mini->charge = 0;
}
