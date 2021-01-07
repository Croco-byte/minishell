/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 17:05:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 1
# define ERROR 0


# define SEPARATORS " \t\r\n\a\v"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <strings.h>
# include <errno.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

# define EMPTY 0
# define CMD 1
# define ARG 2
# define INFILE 3
# define OUTFILE 4
# define APPEND 5
# define END 6
# define PIPE 7

# define STDIN 0
# define STOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define CD_NOTDIR	("Error Opening directory.")
# define CD_NOPEM	("Permission denied.")
# define UNKNOWN_COMMAND	("command not found: ")

typedef struct s_minish
{
	char	**args;
	char	**env;

	int	pid;
	int	parent_pid;
	int	in;
	int	out;
	int	ret;
	int	exit;

}			t_minish;

typedef struct s_token
{
	char	*str;
	int	type;
	struct	s_token	*prev;
	struct	s_token	*next;
}		t_token;

/* DECLARATION OF MAIN FUNCTIONS */
void	minish_loop(t_minish *mini);

/* DECLARATION OF EXEC FUNCTIONS */
void	exec_cmd(t_minish *mini);
void	exec_builtin(t_minish *mini);
void	exec_bin(t_minish *mini);

/* DECLARATION OF BUILTIN FUNCTIONS */
int		ft_pwd(char **args);
int		ft_cd(char **args);
int		ft_echo(char **args);

/* DECLARATION OF PARSING FUNCTIONS */
char	**parse_line(char *line);

/* DECLARATION OF UTILITIES FUNCTIONS */
void	display_args(char **args);
int		is_builtin(char *prog_name);
int		args_number(char **args);

/* DECLARATION OF TYPES */

int	_type(t_token *token, int type);
int	_types(t_token *token, char *types);
int	__pipe(t_token *token);
int	__type(t_token *token, int type);

/* DECLARATION OF PARSER */

int	quotes(char *line, int index);
int	sep(char *line, int i);
int	i_sep(char *line, int i);
int	checkline(t_token *token);
int	valid_arg(t_token *token);
t_token	*prev_separator(t_token *token, int i);



void	ft_prompt(void);
void	free_args(char **args);

#endif



/* TODO QUENTIN :
	- Créer une liste chaînée pour gérer les variables d'environnement.
	- Export sans argument derrière : simple affichage de env. Avec un argument : ajoute la variable à l'environnement.
*/
