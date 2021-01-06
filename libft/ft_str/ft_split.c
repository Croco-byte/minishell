/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:49:40 by user42            #+#    #+#             */
/*   Updated: 2021/01/06 11:42:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**realloc_tab(char **tab, char *str)
{
	char	**nouveau_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	nouveau_tab = malloc(sizeof(char*) * (i + 1 + 1));
	if (!nouveau_tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		nouveau_tab[i] = tab[i];
		i++;
	}
	free(tab);
	nouveau_tab[i] = str;
	nouveau_tab[i + 1] = 0;
	return (nouveau_tab);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*extract_word(const char *s, char *sep, size_t *index)
{
	size_t	j;
	char	*str;

	j = 0;
	while (s[*index + j] && !ft_isinstr(s[*index + j], sep))
		j++;
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	j = 0;
	while (s[*index + j] && !ft_isinstr(s[*index + j], sep))
	{
		str[j] = s[*index + j];
		j++;
	}
	str[j] = 0;
	*index += j;
	return (str);
}

int	initialize(char **tab, size_t *i)
{
	*i = 0;
	if (!tab)
		return (0);
	tab[0] = 0;
	return (1);
}

char	**ft_split(char const *s, char *sep)
{
	char	**tab;
	char	*str;
	size_t	i;

	if (!s || !sep)
		return (0);
	tab = (char **)malloc(sizeof(char *) * 1);
	if (!initialize(tab, &i))
		return (0);
	while (s[i])
	{
		if (ft_isinstr(s[i], sep))
			i++;
		else
		{
			str = extract_word(s, sep, &i);
			if (!str)
			{
				free_tab(tab);
				return (0);
			}
			tab = realloc_tab(tab, str);
		}
	}
	return (tab);
}
