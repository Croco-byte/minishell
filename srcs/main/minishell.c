/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 13:24:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig sig;

/* Ici, il s'agit de la boucle principale de minishell, boucle infinie. A chaque tour de boucle :
 > On affiche le prompt "minishell >"
 > On lit la commande entrée par l'utilisateur grâce à Get_Next_Line, en la stockant char *line, puis en la parsant pour la stocker dans mini->args.
 > On gère le cas particulier d'un signal EOF reçu alors que la ligne est vide : dans ce cas, on quitte proprement, comme dans bash.
 > On exécute la commande parsée.
 >  */

void	minish_loop(t_minish *mini)
{
	char *line;
	int	empty_EOF;

	while(1)
	{
		sig.pid = 0;
		line = 0;
		mini->args = 0;
		ft_prompt();
		empty_EOF = get_next_line(STDIN_FILENO, &line);
		if (empty_EOF == -2)									// --> i.e si on a rencontré un EOF et que la ligne était vide.
		{
			free(line);
			free_strarray(mini->args);
			ft_putstr_fd("exit\n", 1);
			clean_exit(mini);
		}
		mini->args = parse_line(line);
		if (line)
			exec_cmd(mini);
		free(line);
		free_strarray(mini->args);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minish	mini;

	(void)argc;
	(void)argv;
	mini.args = 0;
	mini.env = 0;
	parse_env(&mini, env);
	mini.env = update_env(mini.env, mini.parsed_env);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	minish_loop(&mini);
	free_strarray(mini.env);
	free_parsed_env(mini.parsed_env);
	return (0);
}
