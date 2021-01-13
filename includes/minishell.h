/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 17:38:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR 1

# define ENV_DISP 0
# define EXPORT_DISP 1
# define SEPARATORS " \t\r\n\a\v"

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

# define BUFF_SIZE 2048
# define BIULDUP -28
# define CD_NOTDIR	("Error Opening directory.")
# define CD_NOPEM	("Permission denied.")
# define UNKNOWN_COMMAND	("command not found: ")

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <strings.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

typedef struct s_status
{
	int		pid;
	int		code;
}			t_status;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;


typedef struct s_minish
{
	char	**args;
	char	**env;
	t_env	*parsed_env;
	t_token	*start;

	int	fdin;
	int	fdout;
	int	pid;
	int	parent_pid;
	int	in;
	int	pipin;
	int	out;
	int	pipout;
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

typedef	struct s_build
{
	char	*n_arg;
	int	i;
	//int	;
}		t_build;

/* DECLARATION OF MAIN FUNCTIONS */
void	minish_loop(t_minish *mini);
void	sig_int(int signal);
void	sig_quit(int signal);

/* DECLARATION OF EXEC FUNCTIONS */
void	exec_cmd(t_minish *mini);
int		exec_builtin(t_minish *mini);
int		exec_bin(t_minish *mini);

/* DECLARATION OF BUILTIN FUNCTIONS */
int		ft_pwd(t_minish *mini);
int		ft_cd(t_minish *mini);
int		ft_echo(t_minish *mini);
int		ft_env(t_minish *mini);
int		ft_export(t_minish *mini);
int		ft_unset(t_minish *mini);
void	ft_exit(t_minish *mini);

/* DECLARATION OF ENV FUNCTIONS */
void	parse_env(t_minish *mini, char **env);
char	**update_env(char **env, t_env *parsed_env);
int		get_key_len(char *var);
char	*get_value(char *var, int pos);
int		is_in_env(t_minish *mini, char *var);
t_env	*copy_parsed_env(t_env *parsed_env);
void	sort_parsed_env(t_env *parsed_env);
void	display_parsed_env(t_env *parsed_env, int which);

/* AJOUT D'AUTRES ENV FONCTIONS POUR LA GESTION ? */

int	env_value_size(const char *env);
int	is_env_valid(const char *env);
char	*get_env_value(char *arg, t_env *env);
char	*env_value(char *env);
char	*get_env_name(char *dest, char *src);


/* DECLARATION OF PARSING FUNCTIONS */
char	**parse_line(char *line);

/* DECLARATION OF UTILITIES FUNCTIONS */
int		is_builtin(char *prog_name);
int		args_number(char **args);
int		env_var_nb(t_env *parsed_env);
void	clean_exit(t_minish *mini);
void	ft_prompt(void);
void	display_strarray(char **strarray);
char	**copy_strarray(char **src);
void	sort_strarray(char **to_sort);
void	free_strarray(char **args);
void	free_parsed_env(t_env *parsed_env);

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
t_token	*next_separator(t_token *token, int i);
t_token	*next_cmd(t_token *token, int i);

/* DECLARATION OF BUILDUPS */

int	varcopy(char *arg, const char *value_env, int pos);
int	retsize(int ret);
int	getvar_len(const char *arg, int pos, t_env *env, int ret);
int	get_var_len(const char *arg, int pos, t_env *env, int ret);
int	arg_alloc_size(const char *arg, t_env *env, int ret);

void	insert_var(t_build *build, char *arg, t_env *env, int ret);
char	*builds(char *arg, t_env *env, int ret);
char	*get_var_value(const char *arg, int pos, t_env *env, int ret);

extern t_status status;
extern t_sig g_sig;
#endif



/* TODO QUENTIN :
	- Pour afficher ou trier puis afficher l'environnement, passer par la version parsée.
	- Afficher les valeurs entre guillemets pour l'affichage, comme en bash classique.
*/
