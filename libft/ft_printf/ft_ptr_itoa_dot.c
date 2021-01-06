/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_itoa_dot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:39:44 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:12:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	result_size(long n, t_attr tmp)
{
	int	count;

	count = itoa_size_base(n, 16);
	if (tmp.dot > count)
		count += (tmp.dot - count);
	if (n < 0)
		count++;
	return (count);
}

static char	*case_of_zero(void)
{
	char	*result;

	result = malloc(4 * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, "0x0", 4);
	return (result);
}

static void	reverse_result(char *result)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(result) - 1;
	while (i < j)
	{
		temp = result[i];
		result[i] = result[j];
		result[j] = temp;
		i++;
		j--;
	}
}

char	*ft_ptr_itoa_dot(long n, t_attr tmp)
{
	long	nbr;
	int		i;
	char	*result;
	char	*base;

	base = 0;
	init(base, n, &nbr, &i);
	if (n == 0)
		return (case_of_zero());
	result = malloc((result_size(n, tmp) + 1 + 2) *sizeof(char));
	if (!result)
		return (0);
	nbr = invert_negatives(nbr);
	while (nbr)
	{
		result[i++] = base[nbr % 16];
		nbr /= 16;
	}
	if (n < 0)
		result[i++] = '-';
	result[i++] = 'x';
	result[i++] = '0';
	result[i] = '\0';
	reverse_result(result);
	return (result);
}
