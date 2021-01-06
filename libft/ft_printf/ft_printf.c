/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:46:38 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:12:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_conv(t_attr tmp, va_list argmt)
{
	int	char_nb;

	char_nb = 0;
	if (tmp.type == 'c')
		char_nb = handle_char((char)va_arg(argmt, int), tmp);
	if (tmp.type == 's')
		char_nb = handle_str(va_arg(argmt, char *), tmp);
	if (tmp.type == 'd' || tmp.type == 'i')
		char_nb = handle_int(va_arg(argmt, int), tmp);
	if (tmp.type == 'u')
		char_nb = handle_u(va_arg(argmt, unsigned int), tmp);
	if (tmp.type == 'x' || tmp.type == 'X')
		char_nb = handle_x(va_arg(argmt, unsigned int), tmp);
	if (tmp.type == 'p')
		char_nb = handle_p(va_arg(argmt, long), tmp);
	if (tmp.type == '%')
		char_nb = handle_percent(tmp);
	return (char_nb);
}

int	ft_printf(const char *format, ...)
{
	int				i;
	va_list			argmt;
	t_attr			tmp;
	int				counter;

	i = 0;
	counter = 0;
	if (!format)
		return (counter);
	va_start(argmt, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			tmp = new_attr();
			get_attr(&tmp, format, &i, argmt);
			if (tmp.type != 0)
				counter += print_conv(tmp, argmt);
		}
		else
			counter += ft_putchar_fd(format[i++], 1);
	}
	va_end(argmt);
	return (counter);
}
