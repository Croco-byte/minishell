/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:13:00 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:13:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision_cut(char *str, t_attr tmp)
{
	char	*new_str;

	if (!str)
		str = "(null)";
	if (tmp.dot < 0 || tmp.dot >= (int)ft_strlen(str))
	{
		new_str = malloc(((int)ft_strlen(str) + 1) *sizeof(char));
		if (!new_str)
			return (0);
		ft_strlcpy(new_str, str, (int)ft_strlen(str) + 1);
	}
	else
	{
		new_str = malloc((tmp.dot + 1) *sizeof(char));
		if (!new_str)
			return (0);
		ft_strlcpy(new_str, str, tmp.dot + 1);
	}
	return (new_str);
}

static char	*create_result(t_attr tmp, int str_len)
{
	char	*result;

	if (tmp.width <= str_len)
	{
		result = malloc((str_len + 1) *sizeof(char));
		if (!result)
			return (0);
	}
	else
	{
		result = malloc((tmp.width + 1) *sizeof(char));
		if (!result)
			return (0);
	}
	return (result);
}

static void	fill_right(char *str, char *result, t_attr tmp, int str_len)
{
	int	i;

	i = 0;
	while (i < tmp.width - str_len)
	{
		result[i] = ' ';
		i++;
	}
	ft_strlcpy(result + i, str, str_len + 1);
}

static void	fill_left(char *str, char *result, t_attr tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	while (i < tmp.width)
	{
		result[i] = ' ';
		i++;
	}
	result[i] = '\0';
}

int	handle_str(char *str, t_attr tmp)
{
	int		str_len;
	char	*result;

	str = precision_cut(str, tmp);
	if (!str)
		return (0);
	str_len = (int)ft_strlen(str);
	result = create_result(tmp, str_len);
	if (!result)
		return (0);
	if (tmp.width <= str_len)
		ft_strlcpy(result, str, str_len + 1);
	else
	{
		if (tmp.minus == 0)
			fill_right(str, result, tmp, str_len);
		if (tmp.minus == 1)
			fill_left(str, result, tmp);
	}
	ft_putstr_fd(result, 1);
	str_len = (int)ft_strlen(result);
	free(result);
	free(str);
	return (str_len);
}
