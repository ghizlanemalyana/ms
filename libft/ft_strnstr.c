/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:30:02 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/15 13:17:01 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char			*h;
	char			*n;
	size_t			i;
	size_t			j;

	h = (char *)haystack;
	n = (char *)needle;
	i = 0;
	if (n[0] == 0)
	{
		return (h);
	}
	while (i < len && h[i] != '\0')
	{
		j = 0;
		while (i + j < len && n[j] != '\0' && h[i + j] == n[j])
		{
			j++;
		}
		if (n[j] == '\0')
			return (h + i);
		i++;
	}
	return (NULL);
}
