/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:33:59 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:13:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_result(t_attr tmp)
{
	char	*result;

	if (tmp.width == 0)
	{
		result = malloc(2 * sizeof(char));
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

static void	fill(char c, char *result)
{
	result[0] = c;
	result[1] = '\0';
}

static void	fill_right(char c, char *result, t_attr tmp)
{
	int	i;

	i = 0;
	while (i < (tmp.width - 1))
	{
		result[i] = ' ';
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
}

static void	fill_left(char c, char *result, t_attr tmp)
{
	int	i;

	i = 0;
	result[i] = c;
	while (++i < tmp.width)
		result[i] = ' ';
	result[i] = '\0';
}

int	handle_char(char c, t_attr tmp)
{
	char	*result;
	int		str_len;
	int		k;

	result = create_result(tmp);
	if (!result)
		return (0);
	if (tmp.width <= 1)
		fill(c, result);
	else
	{
		if (tmp.minus == 0)
			fill_right(c, result, tmp);
		if (tmp.minus == 1)
			fill_left(c, result, tmp);
	}
	if (tmp.width == 0)
		str_len = 1;
	else
		str_len = tmp.width;
	k = 0;
	while (k < str_len)
		ft_putchar_fd(result[k++], 1);
	free(result);
	return (str_len);
}
