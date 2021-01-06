/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:35:54 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:12:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_attr(t_attr *tmp, const char *format, int *i, va_list argmt)
{
	*i = (*i) + 1;
	while (format[*i])
	{
		if (!ft_isdigit(format[*i]) && !is_flag(format[*i])
			&& !is_type(format[*i]) && format[*i] != '%')
			break ;
		if (format[*i] == '0')
			extr_zeros_flag(tmp);
		if (format[*i] == '-')
			extr_minus_flag(tmp);
		if (format[*i] == '.')
			extr_dot_flag(tmp, format, i, argmt);
		if (format[*i] == '*' || ft_isdigit(format[*i]))
			extr_width_flag(tmp, format, i, argmt);
		if (is_type(format[*i]) || format[*i] == '%')
		{
			if (is_type(format[*i]))
				tmp->type = format[*i];
			else
				tmp->type = '%';
			*i = (*i) + 1;
			break ;
		}
		*i = (*i) + 1;
	}
}

void	extr_zeros_flag(t_attr *tmp)
{
	if (tmp->width == 0 && tmp->minus == 0)
		tmp->zeros = 1;
}

void	extr_minus_flag(t_attr *tmp)
{
	tmp->minus = 1;
	tmp->zeros = 0;
}

void	extr_width_flag(t_attr *tmp, const char *format, int *i, va_list argmt)
{
	if (format[*i] == '*')
	{
		tmp->star = 1;
		tmp->width = va_arg(argmt, int);
		if (tmp->width < 0)
		{
			tmp->minus = 1;
			tmp->zeros = 0;
			tmp->width *= -1;
		}
	}
	else
	{
		if (tmp->star == 1)
		{
			tmp->width = 0;
			tmp->star = 0;
		}
		tmp->width = tmp->width * 10 + (format[*i] - 48);
	}
}

void	extr_dot_flag(t_attr *tmp, const char *format, int *i, va_list argmt)
{
	*i = (*i) + 1;
	tmp->dot = 0;
	while (ft_isdigit(format[*i]) || format[*i] == '*' || format[*i] == '-')
	{
		if (ft_isdigit(format[*i]))
		{
			if (tmp->star == 1)
			{
				tmp->dot = 0;
				tmp->star = 0;
			}
			tmp->dot = tmp->dot * 10 + (format[*i] - 48);
		}
		else if (format[*i] == '*')
		{
			tmp->star = 1;
			tmp->dot = va_arg(argmt, int);
		}
		else
			extr_minus_flag(tmp);
		*i = (*i) + 1;
	}
	if (tmp->dot >= 0 && format[*i] != '%')
		tmp->zeros = 0;
}
