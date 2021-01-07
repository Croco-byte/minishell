/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 18:02:51 by user42           ###   ########.fr       */
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
}			t_minish;


/* DECLARATION OF MAIN FUNCTIONS */
void	minish_loop(t_minish *mini);

/* DECLARATION OF EXEC FUNCTIONS */
void	exec_cmd(t_minish *mini);
void	exec_builtin(t_minish *mini);
void	exec_bin(t_minish *mini);

/* DECLARATION OF BUILTIN FUNCTIONS */
int		ft_pwd(t_minish *mini);
int		ft_cd(t_minish *mini);
int		ft_echo(t_minish *mini);
int		ft_env(t_minish *mini);
int		ft_export(t_minish *mini);

/* DECLARATION OF ENV FUNCTIONS */
void	parse_env(t_minish *mini, char **env);
char	**update_env(char **env, t_env *parsed_env);
int		get_key_len(char *var);
char	*get_value(char *var, int pos);

/* DECLARATION OF PARSING FUNCTIONS */
char	**parse_line(char *line);

/* DECLARATION OF UTILITIES FUNCTIONS */
int		is_builtin(char *prog_name);
int		args_number(char **args);
int		env_var_nb(t_env *parsed_env);
void	ft_prompt(void);
void	display_strarray(char **strarray);
char	**copy_strarray(char **src);
void	sort_strarray(char **to_sort);
void	free_strarray(char **args);
void	free_parsed_env(t_env *parsed_env);


#endif



/* TODO QUENTIN :
	- Pour afficher ou trier puis afficher l'environnement, passer par la version parsée.
	- Afficher les valeurs entre guillemets pour l'affichage, comme en bash classique.
*/
