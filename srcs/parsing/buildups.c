#include "minishell.h"

int	varcopy(char *newarg, const char *env_value, int pos)
{
	int	i;

	i = 0;
	while (env_value[i])
		newarg[pos++] = env_value[i++];
	return (i);
}

void	insert_var(t_build *build, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, build->j, env, ret);
	build->i += env_value ? varcopy(build->str, env_value, build->i) : 0;
	ft_memdel(env_value);
	arg[build->j] == '?' ? build->j++ : 0;
	if (ft_isdigit(arg[build->j]) == 0 && arg[build->j - 1] != '?')
	{
		while (is_env_char(arg[build->j]) == 1)
			build->j++;
	}
	else
	{
		if (arg[build->j - 1] != '?')
			build->j++;
	}
}

char	*builds(char *arg, t_env *env, int ret)
{
	t_build	*build;
	int	n_arg_len;

	n_arg_len = arg_alloc_size(arg, env, ret);
	if (!(build->n_arg = malloc(sizeof(char) * n_arg_len + 1)))
		return (NULL);
	build->i = 0;
	build->j = 0;
	while (build->i < n_arg_len && arg[build->j])
	{
		while (arg[build->j] == BIULDUP)
		{
			build->j++;
			if ((arg[build->j] == '\0' || ft_isalnum(arg[build->j]) == 0) && arg[build->j] != '?')
				build->n_arg[build->i++] = '$';
			else
				insert_var(build, arg, env, ret);
		}
		build->n_arg[build->i++] = arg[build->j++];
	}
	build->n_arg[build->i] = '\0';
	return (build->n_arg);
}


