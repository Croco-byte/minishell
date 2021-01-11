#include "minishell.h"

char	*get_env_value(char *arg, t_env *env)
{
	char	env_n[BUFF_SIZE];
	char	*env_value;
	int i;

	i = 0;

	env_value = ft_strdup("");
	while (env[i] && env[i].value)
	{
		get_env_name(env_n, env[i].value);
		if (ft_strcmp(agr, env_n) == 0)
		{
			ft_memdel(env_value);
			env_value = env_value(env[i].value);
			return (env_value);
		}
		i++;
	}
	return (env_value);
}

int	env_value_size(const char *env)
{
	int	i;
	int	size;
	int	j;	

	size = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	j = i + 1;
	while (env[j])
	{
		j++;
		size++;
	}
	return (size);
}

char	*env_value(char *env)
{
	int	i;
	int	j;
	int	value;
	char	*env_value;

	if (!(env_value = malloc(sizeof(char) * (env_value_size(env) + 1))))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}	

char	*get_env_name(char ùdest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_env_valid(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}