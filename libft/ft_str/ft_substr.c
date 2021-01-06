/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 09:42:08 by user42            #+#    #+#             */
/*   Updated: 2021/01/03 15:43:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	substr_size(char const *s, unsigned int start, size_t len)
{
	int	i;

	i = 0;
	if (start + len <= ft_strlen(s))
		return ((int)len);
	else
	{
		while (s[start + i])
			i++;
		return (i);
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (start > ft_strlen(s) || !s || len == 0)
	{
		substr = malloc(1 * sizeof(char));
		if (!substr)
			return (0);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc((substr_size(s, start, len) + 1) *sizeof(char));
	if (!substr)
		return (0);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
