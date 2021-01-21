/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:39:46 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 17:11:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && !is_escaped(line, i))
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

int		quote_check(t_minish *mini, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		status.code = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	display_chained_list(t_minish *mini)
{
	while (mini->start->next)
	{
		printf("%s [TYPE %i] ; ", mini->start->str, mini->start->type);
		mini->start = mini->start->next;
	}
	printf("%s [TYPE %i] ", mini->start->str, mini->start->type);
	printf("\n");
	while (mini->start && mini->start->prev)
		mini->start = mini->start->prev;
}

void	parse(t_minish *mini)
{
	char	*line;
	t_token	*token;

	line = 0;
	ft_prompt();
	if (get_next_line(0, &line) == -2)
	{
		free(line);
		ft_putendl_fd("exit", STDERR);
		clean_exit(mini);
	}
	if (quote_check(mini, &line))
		return ;
	line = space_line(line);
//	ft_printf("Line : %s\n", line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->start = get_tokens(line);
//	display_chained_list(mini);
	ft_memdel(line);
	squish_args(mini);
	token = mini->start;
	while (token)
	{
		if (is_tok_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
//	display_chained_list(mini);
}
