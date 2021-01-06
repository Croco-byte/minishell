/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:37:06 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:13:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_result(t_attr tmp, int nb_len)
{
	char	*result;

	if (tmp.width > nb_len && tmp.width > tmp.dot)
	{
		result = malloc((tmp.width + 1) *sizeof(char));
		if (!result)
			return (0);
	}
	else if (tmp.dot > nb_len && tmp.dot > tmp.width)
	{
		result = malloc((tmp.dot + 1) *sizeof(char));
		if (!result)
			return (0);
	}
	else
	{
		result = malloc((nb_len + 1) *sizeof(char));
		if (!result)
			return (0);
	}
	return (result);
}

static void	fill_right(char *nb_str, char *result, t_attr tmp, int nb_len)
{
	int	i;

	i = 0;
	while (i < tmp.width - nb_len)
	{
		result[i] = ' ';
		i++;
	}
	ft_strlcpy(result + i, nb_str, nb_len + 1);
}

static void	fill_left(char *nb_str, char *result, t_attr tmp)
{
	int	i;

	i = 0;
	while (nb_str[i])
	{
		result[i] = nb_str[i];
		i++;
	}
	while (i < tmp.width)
	{
		result[i] = ' ';
		i++;
	}
	result[i] = '\0';
}

int	handle_p(long nb, t_attr tmp)
{
	char	*result;
	char	*nb_str;
	int		nb_len;

	nb_str = ft_ptr_itoa_dot(nb, tmp);
	if (!nb_str)
		return (0);
	nb_len = (int)ft_strlen(nb_str);
	result = create_result(tmp, nb_len);
	if (!result)
		return (0);
	if (tmp.width <= nb_len)
		ft_strlcpy(result, nb_str, nb_len + 1);
	else
	{
		if (tmp.minus == 0)
			fill_right(nb_str, result, tmp, nb_len);
		if (tmp.minus == 1)
			fill_left(nb_str, result, tmp);
	}
	ft_putstr_fd(result, 1);
	nb_len = (int)ft_strlen(result);
	free(nb_str);
	free(result);
	return (nb_len);
}
