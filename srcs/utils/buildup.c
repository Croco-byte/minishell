#include "minishell.h"

int	retsize(int ret)
{
	char *tmp;
	int	len;

	tmp = ft_itoa(ret);
	len = ft_strlen(tmp);
	ft_memdel(tmp);
	return(len);
}

int	getvar_len(const char *arg, int pos, t_env *env, int ret)
{
	char	*var_val;
	char	var_n[BUFF_SIZE];
	int	i;

	i = 0;
	if (ft_isdigit(arg[pos]))
		return (0);
	if (arg[pos] == '?')
		return (retsize(ret));
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_n[i] = arg[pos];
		i++;
		pos++;
	}
	var_n[i] = '\0';
	var_val = get_env_value(var_n, env);
	i = ft_strlen(var_val);
	ft_memdel(var_val);	
	return (i);
}

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_n[BUFF_SIZE];
	char	*var_val;
	int	i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_val = ft_itoa(ret);
		return (var_val);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_n[i] = arg[pos];
		i++;
		pos++;
	}
	var_n[i] = '\0';
	var_val = get_env_value(var_n, env);
	return (var_val);
}

int	get_var_len(const char *arh, int pos, t_env *env, int ret)
{
	char	var_n[BUFF_SIZE];
	char	*var_val;
	int	i;

	i = 0;
	if (ft_isdigit(arg[pos]))
		return (0);
	if (arg[pos] == '?')
		return (retsize(ret));
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_n[i] = arg[pos];
		i++;
		pos++;
	}
	var_n[i] = '\0';
	var_val = get_env_value(var_n, env);
	i = ft_strlen(var_val);
	ft_memdel(var_val);
	return(i);
}

int	arg_alloc_size(const char *arg, t_env *env, int ret)
{
	int i;
	int size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == BIULDUP)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i] == 0))
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

