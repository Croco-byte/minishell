/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:26:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 15:49:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	tool;

	tool = (long)n;
	if (tool < 0)
	{
		tool *= -1;
		ft_putchar_fd('-', fd);
	}
	if (tool > 9)
		ft_putnbr_fd(tool / 10, fd);
	ft_putchar_fd((tool % 10) + 48, fd);
}
