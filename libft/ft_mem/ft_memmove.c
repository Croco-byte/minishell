/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:29:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 15:54:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	unsafe_overlap(void *dest, const void *src, size_t n)
{
	if (src < dest && dest <= src + n)
		return (1);
	else
		return (0);
}

static void	reverse_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	while (i--)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (0);
	if (unsafe_overlap(dest, src, n))
	{
		reverse_memcpy(dest, src, n);
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
