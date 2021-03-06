/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:53:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	int		has_space;
	char	*key;
	char	*value;
}			t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

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

void	prefix_path(char *path, char **cmd, int i);
void	add_path(t_minish *mini, char **cmd);

int		is_ignored_char(char *cmd, int i);
char	*strip_quotes(char *cmd);
char	**delete_arg(char **cmd, int i);

/* DECLARATION OF BUILTIN FUNCTIONS */
int		ft_pwd(t_minish *mini, char **cmd);
int		ft_echo(char **cmd);
int		ft_env(t_minish *mini, char **cmd);
int		ft_export(t_minish *mini, char **cmd);
int		ft_unset(t_minish *mini, char **cmd);
int		ft_exit(t_minish *mini, char **cmd);

int		ft_cd(t_minish *mini, char **cmd);
int		env_pos(t_minish *mini, char *name);
int		cd_home(t_minish *mini, char **cmd);
int		cd_oldpwd(t_minish *mini, char **cmd);
void	update_oldpwd(t_minish *mini, char *cwd);
void	add_cd_path(t_minish *mini, char **cmd);
void	update_pwd(t_minish *mini, char **cmd);

/* DECLARATION OF ENV FUNCTIONS */
void	parse_env(t_minish *mini, char **env);
char	**update_env(char **env, t_env *parsed_env);
int		get_key_len(char *var);
char	*get_value(char *var, int pos, int i, t_env *parsed_env);

int		is_in_env(t_minish *mini, char *var);
int		is_env_var(char *var);

t_env	*copy_parsed_env(t_env *parsed_env);
void	sort_parsed_env(t_env *parsed_env);
void	display_parsed_env(t_env *parsed_env, int which);
int		display_sorted(t_minish *mini);

void	add_env_var(t_minish *mini, char *var);
void	repl_env_var(t_minish *mini, t_env *parsed_env, char *var, int pos);

void	increase_shell_level(t_minish *mini);

/* DECLARATION OF PARSING FUNCTIONS */
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

void	display_chained_list(t_minish *mini);

extern t_status	g_status;
#endif

/* TODO
> [DONE]	Affichage de env : retirer le "declare -x" qui n'est pr??sent que dans le cadre de la commande export.
> [DONE]	G??rer cd ~ (variable d'environnement HOME)
> [DONE]	G??rer cd - (variable d'environnement OLDPWD)
> [DONE]	G??rer le cas des backslashs : si un backslash est escape, il ne neutralise pas le caract??re suivant. Exemple : echo "Hello \\$PATH" doit afficher la variable d'environnement PATH.
> [DONE]	G??rer le cas de echo : "echo -nnnnnnn hi" doit fonctionner comme "echo -n hi".
> [DONE]	Modifier les affichages de message d'erreur pour qu'ils aillent bien vers STDERR et pas STDOUT.
> [DONE]	S'occuper de la variable d'environnement shell level.
> [DONE]	S'assurer que, dans la commande, les tabulations, new_lines etc... soient bien trait??s comme des espaces.
> [DONE]	La commande "env" ne doit pas afficher de variable vide. La commande "export" doit l'afficher sur le mod??le declare -x VAR.
> [DONE]	Les additions aux variables d'environnement existantes doivent ??tre g??r??es (export test+=<added to var value>).
> [DONE]	G??rer les arguments de "exit".
> [DONE]	G??rer la variable CDPATH.
> [DONE]	G??rer l'escaping diff??rent quand on est entre quotes
> [DONE]	G??rer le code d'erreur de "export ="
> [DONE]	R??gler le cas de "export HOME=", qui ne vide pas la variable existante HOME.
> [DONE]	export test= : affiche test= dans "env", affiche declare -x test="" dans "export" ; "export test" n'affiche rien dans "env", et affiche declare -x test dans "export".
> [DONE]	export HOME (sans ??gal) ne remplace PAS la variable HOME existante ; export HOME= remplace la variable HOME existante par du vide.
> [DONE]	SIGINT affiche un code d'erreur 2 au lieu de 130.
> [DONE]	cd ; pwd
> [DONE]	mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd
> [DONE]	echo $TEST$TEST=lol$TEST""lol
*/
