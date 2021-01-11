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
	//continue
	return (1);
}


