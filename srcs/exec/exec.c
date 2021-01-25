/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:09:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/25 16:32:44 by user42           ###   ########.fr       */
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

int		no_quotes_len(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' && quotes(cmd, i) != 2 && !is_escaped(cmd, i))
			i++;
		else if (cmd[i] == '\'' && quotes(cmd, i) != 1 && !is_escaped(cmd, i))
			i++;
		else if(cmd[i] == '\\' && quotes(cmd, i) != 1 && quotes(cmd, i) != 2 && !is_escaped(cmd, i))
			i++;
		else if (cmd[i] == '\\' && quotes(cmd, i) == 1 && cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '\"' || cmd[i + 1] == '$') && !(is_escaped(cmd, i)))
			i++;
		else if (cmd[i] == '\\' && quotes(cmd, i) == 2 && cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '\'' || cmd[i + 1] == '$') && !(is_escaped(cmd, i)))
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

	result = malloc((no_quotes_len(cmd) + 1) * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' && quotes(cmd, i) != 2 && !is_escaped(cmd, i))
			i++;
		else if (cmd[i] == '\'' && quotes(cmd, i) != 1 && !is_escaped(cmd, i))
			i++;
		else if(cmd[i] == '\\' && quotes(cmd, i) != 1 && quotes(cmd, i) != 2 && !is_escaped(cmd, i))
			i++;
		else if (cmd[i] == '\\' && quotes(cmd, i) == 1 && cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '\"' || cmd[i + 1] == '$') && !(is_escaped(cmd, i)))
			i++;
		else if (cmd[i] == '\\' && quotes(cmd, i) == 2 && cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '\'' || cmd[i + 1] == '$') && !(is_escaped(cmd, i)))
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
	int	j;

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
	i = 0;
	while (cmd && cmd[i] && cmd[i + 1])
	{
		if (cmd[i][0] == '\0')
			cmd = delete_arg(cmd, i);
		i++;
	}
	if (cmd && cmd[i] && cmd[i][0] == '\0')
		cmd = delete_arg(cmd, i);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = strip_quotes(cmd[i]);
//		printf("cmd[%i] = |%s|\n", i, cmd[i]);
		i++;
	}
	if (cmd[0] && is_builtin(cmd[0]))
		status.code = exec_builtin(mini, cmd);
	else if (cmd[0])
		exec_bin(mini, cmd);

	free_strarray(cmd);
	mini->charge = 0;
}
