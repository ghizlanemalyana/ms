/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:14:44 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/15 17:00:55 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_num(char const *s, char c)
{
	char	last;
	size_t	i;
	size_t	j;

	last = c;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (last == c && s[i] != c)
		{
			j++;
		}
		last = s[i];
		i++;
	}
	return (j);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	return (j);
}

static char	**ft_free(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free (arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	size_t			i;
	size_t			j;

	if (!s)
		return (NULL);
	i = -1;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (get_word_num(s, c) + 1));
	if (!arr)
		return (NULL);
	while (++i < get_word_num(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
		{
			arr[i] = ft_substr(s, j, get_word_len(&s[j], c));
			if (!arr[i])
				return (ft_free(arr, i));
			j += get_word_len(&s[j], c);
		}
	}
	arr[i] = NULL;
	return (arr);
}
