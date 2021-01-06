/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 15:56:37 by user42           ###   ########.fr       */
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

/* DECLARATION OF MAIN FUNCTIONS */


/* DECLARATION OF EXEC FUNCTIONS */
void	exec_cmd(char **args);
void	exec_builtin(char **args);
void	exec_bin(char **args);

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
void	ft_prompt(void);
void	free_args(char **args);

#endif
