#include "minishell.h"

char	*alloc_space(char *line)
{
	char *space;
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (line[++i])
		if (sep(line, i))
			count++;
	if (!(space = malloc(sizeof(char) + (i + (2 * count) + 1))))
		return (NULL);
	return (space);
}

char *space_line(char *line)
{
	char	*space;
	int	i;
	int	j;

	i = -1;
	j = 0;
	space = alloc_space(line);
	while (space && line[++i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] !='\\')
			space[j++] = char(-line[i]);
		else if (quotes(line, i) == 0 && sep(line, i))
		{
			space[j++] = ' ';
			space[j++] = line[i];
			if (quotes(line, i) == 0 && line[i] == '>')
				space[j++] = line[i];
			space[j++] = ' ';
		}
		else
			space[j++] = line[i];
	}
	space[j] = '\0';
	ft_memdel(line);
	return (space);
}

int	check_quotes(t_minish *mini, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	parse_line(t_minish *mini)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	mini->ret ? ft_putstr_fd("KO ", STDERR) : ft_putstr_fd("OK ", STDERR);
	ft_putstr_fd("minishell> ", STDERR);
	if (get_next_line(0, &line) == -2 && (mini->exit = 1))
		ft_putendl_fd("exit", STDERR);
	mini->ret = (g_sig.sigint == 1) ? g_sig.exit_status : miniÃ->ret;
	if (quote_check(mini, &line))
		return;
	line = space_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->start = get_tokens(line);
	ft_memdel(line);
	_args(mini);
	token = mini->start;
	while (token)
	{
		if (_type(token, ARG))
			arg_type(token, 0);
		token = token->next;
	}
}
