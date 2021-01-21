/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 15:34:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define ERROR 1

# define SEPARATORS " \t\r\n\a\v"

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 2048

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

typedef struct s_token
{
	char	*str;
	int		type;
	struct	s_token	*prev;
	struct	s_token	*next;
}		t_token;

typedef struct s_minish
{
	char	**env;
	t_env	*parsed_env;

	t_token	*start;


	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		no_exec;
	int		parent;
	int		last;
	int		charge;

	int		pid;


}			t_minish;

/* DECLARATION OF MAIN FUNCTIONS */
void	minish_loop(t_minish *mini);
void	sig_int(int signal);
void	sig_quit(int signal);
void	redir(t_minish *mini, t_token *token, int type);
void	input(t_minish *mini, t_token *token);
int		minipipe(t_minish *mini);

/* DECLARATION OF EXEC FUNCTIONS */
void	exec_cmd(t_minish *mini, t_token *token);
int		exec_builtin(t_minish *mini, char **cmd);
int		exec_bin(t_minish *mini, char **cmd);

/* DECLARATION OF BUILTIN FUNCTIONS */
int		ft_pwd(char **cmd);
int		ft_cd(t_minish *mini, char **cmd);
int		ft_echo(char **cmd);
int		ft_env(t_minish *mini, char **cmd);
int		ft_export(t_minish *mini, char **cmd);
int		ft_unset(t_minish *mini, char **cmd);
void	ft_exit(t_minish *mini, char **cmd);

void	add_env_var(t_minish *mini, char *var);
void	repl_env_var(t_minish *mini, t_env *parsed_env, char *var, int pos);

/* DECLARATION OF ENV FUNCTIONS */
void	parse_env(t_minish *mini, char **env);
char	**update_env(char **env, t_env *parsed_env);
int		get_key_len(char *var);
char	*get_value(char *var, int pos);
int		is_in_env(t_minish *mini, char *var);
t_env	*copy_parsed_env(t_env *parsed_env);
void	sort_parsed_env(t_env *parsed_env);
void	display_parsed_env(t_env *parsed_env, int which);
void	increase_shell_level(t_minish *mini);

/* DECLARATION OF PARSING FUNCTIONS */
char	**parse_line_temp(char *line);
void	parse(t_minish *mini);
void	display_chained_list(t_minish *mini);
void	type_arg(t_token *token, int separator);
void	squish_args(t_minish *mini);
int		next_alloc(char *line, int *i);
t_token	*next_token(char *line, int *i);
t_token	*get_tokens(char *line);

char	*expand(t_minish *mini, char *arg);

/* DECLARATION OF UTILITIES FUNCTIONS */
void	mini_init(t_minish *mini, char **env);
void	sig_init(void);

void	ft_close(int fd);
void	reset_std(t_minish *mini);
void	close_fds(t_minish *mini);
void	reset_fds(t_minish *mini);

int		is_builtin(char *prog_name);
int		args_number(char **args);
int		env_var_nb(t_env *parsed_env);
void	clean_exit(t_minish *mini);
void	free_token(t_token *start);
void	ft_prompt(void);
void	display_strarray(char **strarray);
char	**copy_strarray(char **src);
void	sort_strarray(char **to_sort);
void	free_strarray(char **args);
void	free_parsed_env(t_env *parsed_env);
void	*ft_memdel(void *ptr);

int		is_sep(char *line, int i);
int		ignore_sep(char *line, int i);
int		quotes(char *line, int index);
int		is_last_valid_arg(t_token *token);
int		check_line(t_token *token);

t_token	*next_run(t_token *token, int skip);
t_token	*prev_sep(t_token *token, int skip);
t_token	*next_sep(t_token *token, int skip);

t_token	*next_type(t_token *token, int type, int skip);
int		has_pipe(t_token *token);
int		has_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		is_tok_type(t_token *token, int type);

int		char_in_str(char *str, char c);
int		var_end_dist(char *str, int index);
int		exp_in_env(t_minish *mini, char *arg, int begin);
void	replace_str(char *result, char *src, char *to_insert, int index);
void	replace_code(char *result, char *src, char *to_insert, int index);

int		is_escaped(char *str, int index);


extern t_status status;
#endif


/* TODO
> [DONE]	Affichage de env : retirer le "declare -x" qui n'est présent que dans le cadre de la commande export.
> [DONE]	Gérer cd ~ (variable d'environnement HOME)
> [DONE]	Gérer cd - (variable d'environnement OLDPWD)
> [DONE]	Gérer le cas des backslashs : si un backslash est escape, il ne neutralise pas le caractère suivant. Exemple : echo "Hello \\$PATH" doit afficher la variable d'environnement PATH.
> 			Gérer le cas de echo : "echo -nnnnnnn hi" doit fonctionner comme "echo -n hi".
> [DONE]	Modifier les affichages de message d'erreur pour qu'ils aillent bien vers STDERR et pas STDOUT.
> [DONE]	S'occuper de la variable d'environnement shell level.
> [DONE]	S'assurer que, dans la commande, les tabulations, new_lines etc... soient bien traités comme des espaces.


BUGS TO FIX :
> [DONE]	cd ; pwd
> [~DONE~]	Comportement étrange dans bash, on ne gère pas : mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd
> 			echo $TEST$TEST=lol$TEST""lol

*/
