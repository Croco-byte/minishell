/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:24:42 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 12:45:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Il s'agit ici des fonctions de gestion des signaux. Pour résumer, lorsque minishell intercepte un signal SIGINT (CTRL + C) :
 > S'il n'y a pas de programme en train de tourner, on revient à la ligne et on affiche le prompt.
 > Si un programme tourne, on revient juste à la ligne.

 Lorsque minishell intercepte un signal SIGQUIT (CTRL + \) :
 > S'il n'y a pas de programme en train de tourner, on affiche rien (\b\b  \b\b pour camoufler le ^\).
 > Si un programme tourne, on affiche "Quit (core dumped)" comme dans bash.

 Explications plus détaillées ci-dessous. */

/* Each iteration of the main loop, we are resetting status.pid to 0. If status.pid is still 0 when the SIGINT SIGNAL is caught, it means we are still on the process of our shell
 (no child process is running). We then hide the ^C, jump line, and display the prompt again. If there was a beginning of command in the prompt before SIGINT, it
 won't be taken into account since we didn't hit "Enter", and so Get_next_line didn't buffer anything.

 If status.pid isn't 0 when SIGINT is caught, it means that it was changed by the fork() call, and couldn't be reset after the child process exited. It then means that there
 is a running child process. The SIGINT signal will be sent to both the parent and child process. The child process erased all signal handlers when, after the fork, the
 exec call have been made. The child process will then simply with its own signal handlers, or more probably, keep the default behavior of the signal. It will then be
 interrupted. In such a case, the parent process only has to jump a line, since after the child was interrupted, the waitpid function will allow the parent process to
 continue, and it will display the prompt normally, in the next iteration of the main loop.
 */

void	sig_int(int signal)
{
	(void)signal;
	if (status.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[1;31m🐊 minishell ▸ \033[0m", STDERR);
	}
	else
		ft_putstr_fd("\n", STDERR);
	status.code = 130;
}

void	sig_quit(int sign)
{
	(void)sign;
	if (status.pid != 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR);
		status.code = 131;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}
