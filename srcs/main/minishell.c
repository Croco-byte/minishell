/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:39:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 12:57:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status status;

/* Ici, il s'agit de la boucle principale de minishell, boucle infinie. A chaque tour de boucle :
 > On affiche le prompt "minishell >"
 > On lit la commande entrée par l'utilisateur grâce à Get_Next_Line, en la stockant char *line, puis en la parsant pour la stocker dans mini->args.
 > On gère le cas particulier d'un signal EOF reçu alors que la ligne est vide : dans ce cas, on quitte proprement, comme dans bash.
 > On exécute la commande parsée.
 >  */

void	redir_and_exec(t_minish *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_tok_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_tok_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_tok_type(prev, INPUT))
		input(mini, token);
	else if (is_tok_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_tok_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_tok_type(prev, END) || is_tok_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	minish(t_minish *mini)
{
	t_token *token;
	int	exit_code;

	token = next_run(mini->start, NOSKIP);
	token = (is_types(mini->start, "TAI")) ? mini->start->next : token;
	while (token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exec(mini, token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &exit_code, 0);
		if (mini->last == 0)
			status.code = WEXITSTATUS(exit_code);
		if (mini->parent == 0)
		{
			free_token(mini->start);
			exit(status.code);
		}
		ft_putstr_fd("[DEBUG] Last command returned ", STDERR);
		ft_putnbr_fd(status.code, STDERR);
		ft_putchar_fd('\n', STDERR);
		mini->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

void	minish_loop(t_minish *mini)
{
	while(1)
	{
		status.pid = 0;
		mini->start = 0;
		parse(mini);
		if (mini->start && check_line(mini->start))
			minish(mini);
		free_token(mini->start);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_minish	mini;

	(void)argc;
	(void)argv;
	status.code = 0;
	mini_init(&mini, env);
	sig_init();
	minish_loop(&mini);
	return (0);
}
