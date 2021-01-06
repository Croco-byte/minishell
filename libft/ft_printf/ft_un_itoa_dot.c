/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_un_itoa_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:26:19 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 15:12:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	result_size(unsigned int n, t_attr tmp)
{
	int	count;

	count = itoa_un_size_base(n, 10);
	if (tmp.dot > count)
		count += (tmp.dot - count);
	if (n < 0)
		count++;
	return (count);
}

static char	*case_of_zero(t_attr tmp)
{
	char	*result;
	int		count;
	int		k;

	k = 0;
	count = 1;
	if (tmp.dot > count)
		count += (tmp.dot - count);
	result = malloc((count + 1) *sizeof(char));
	if (!result)
		return (0);
	if (tmp.dot > 1)
	{
		while (k < tmp.dot - 1)
		{
			result[k] = '0';
			k++;
		}
	}
	if (tmp.dot)
		result[k++] = '0';
	result[k] = '\0';
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

static void	handle_prec(unsigned int n, char *result, int *i, t_attr tmp)
{
	int	k;
	int	count;

	count = itoa_un_size_base(n, 10);
	k = 0;
	if (tmp.dot > count)
	{
		while (k < tmp.dot - count)
		{
			result[*i] = '0';
			k++;
			*i = (*i) + 1;
		}
	}
}

char	*ft_un_itoa_dot(unsigned int n, t_attr tmp)
{
	long	nbr;
	int		i;
	char	*result;

	nbr = (long)n;
	i = 0;
	if (n == 0)
		return (case_of_zero(tmp));
	result = malloc((result_size(n, tmp) + 1) *sizeof(char));
	if (!result)
		return (0);
	while (nbr)
	{
		result[i] = (nbr % 10) + 48;
		nbr /= 10;
		i++;
	}
	handle_prec(n, result, &i, tmp);
	result[i] = '\0';
	reverse_result(result);
	return (result);
}
