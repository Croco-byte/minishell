/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:25:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:55:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_attr
{
	int			minus;
	int			zeros;
	int			width;
	int			dot;
	int			star;
	char		type;
}				t_attr;

t_attr	new_attr(void);
void	get_attr(t_attr *tmp, const char *format, int *i, va_list argmt);
void	extr_zeros_flag(t_attr *tmp);
void	extr_minus_flag(t_attr *tmp);
void	extr_width_flag(t_attr *tmp, const char *format, int *i, va_list argmt);
void	extr_dot_flag(t_attr *tmp, const char *format, int *i, va_list argmt);
int		ft_printf(const char *format, ...);
int		is_flag(char c);
int		is_type(char c);
int		print_conv(t_attr tmp, va_list argmt);
int		handle_char(char c, t_attr tmp);
int		handle_str(char *str, t_attr tmp);
int		handle_int(int nb, t_attr tmp);
int		itoa_size_base(long n, int base_size);
int		itoa_un_size_base(unsigned int n, int base_size);
char	*ft_itoa_dot(int n, t_attr tmp);
char	*ft_un_itoa_dot(unsigned int n, t_attr tmp);
char	*ft_un_itoa_base_dot(unsigned int n, t_attr tmp);
char	*ft_ptr_itoa_dot(long n, t_attr tmp);
int		handle_u(unsigned int nb, t_attr tmp);
int		handle_x(unsigned int nb, t_attr tmp);
int		handle_p(long nb, t_attr tmp);
int		handle_percent(t_attr tmp);
long	invert_negatives(long nbr);
void	init(char *base, long n, long *nbr, int *i);
void	init2(char c, char *base, int *i);

#endif
