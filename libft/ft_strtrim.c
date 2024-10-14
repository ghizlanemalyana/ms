/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:40:54 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/10 20:15:44 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;
	size_t	trimmed_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && end && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	trimmed_len = end - start;
	ptr = (char *)malloc(trimmed_len + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1 + start, trimmed_len);
	ptr[trimmed_len] = '\0';
	return (ptr);
}
