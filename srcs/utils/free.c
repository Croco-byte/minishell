/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:44:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 12:37:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonctions utilitaires pour free nos variables avant de quitter */

void	clean_exit(t_minish *mini)
{
//	ft_putendl_fd("Bye ! 👋", 1);
	free_strarray(mini->env);
	free_parsed_env(mini->parsed_env);
	free_token(mini->start);
//	ft_printf("[DEBUG] Exiting with code : %i\n", status.code);
	exit(status.code);
}

void	free_strarray(char **args)
{
	int i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_parsed_env(t_env *parsed_env)
{
	int i;

	i = 0;
	if (!parsed_env)
		return ;
	while (parsed_env[i].key)
	{
		free(parsed_env[i].key);
		free(parsed_env[i].value);
		i++;
	}
	free(parsed_env);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		ft_memdel(start->str);
		start = start->next;
		ft_memdel(start->prev);
	}
	if (start)
	{
		ft_memdel(start->str);
		ft_memdel(start);
	}
}
