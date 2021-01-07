/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:04:06 by user42            #+#    #+#             */
/*   Updated: 2021/01/07 17:13:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_return(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnljoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	s1_size;
	size_t	s2_size;
	char	*result;

	i = -1;
	k = -1;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (!s1 && !s2)
		return (0);
	result = malloc((s1_size + s2_size + 1) *sizeof(char));
	if (!result)
		return (0);
	while (++i < s1_size)
		result[i] = s1[i];
	while (++k < s2_size)
		result[i + k] = s2[k];
	result[i + k] = '\0';
	free((char *)s1);
	return (result);
}

int	is_last_line(char *save, int *last_line, int i)
{
	if (!save[i])
	{
		*last_line = 1;
		free(save);
		return (1);
	}
	else
		return (0);
}

char	*update_save(char *save, int *last_line)
{
	int		i;
	int		k;
	char	*new_save;

	i = 0;
	k = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (is_last_line(save, last_line, i))
		return (0);
	else
		i++;
	new_save = malloc(((ft_strlen(save) - i) + 1) *sizeof(char));
	if (!new_save)
	{
		free(save);
		return (0);
	}
	while (save[i])
		new_save[k++] = save[i++];
	new_save[k] = '\0';
	free(save);
	return (new_save);
}
