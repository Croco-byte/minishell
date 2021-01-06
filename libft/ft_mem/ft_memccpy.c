/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:33:27 by user42            #+#    #+#             */
/*   Updated: 2020/11/19 14:43:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc_dest;
	unsigned char	*uc_src;
	unsigned char	uc_c;

	uc_dest = (unsigned char *)dest;
	uc_src = (unsigned char *)src;
	uc_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		uc_dest[i] = uc_src[i];
		if (uc_src[i] == uc_c)
			return (dest + i + 1);
		i++;
	}
	return (0);
}
