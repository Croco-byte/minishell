/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:09:22 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 17:40:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Si le premier argument de la commande est un builtin, on envoie la commande aux fonctions builtins. Sinon, c'est un binary, on l'envoie vers la fonction qui
gère l'exécution des binaries. */

void	exec_cmd(t_minish *mini)
{
	if (mini->args[0] && is_builtin(mini->args[0]))
		status.code = exec_builtin(mini);
	else if (mini->args[0])
		status.code = exec_bin(mini);
}
