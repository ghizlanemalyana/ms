/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:13:49 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/15 20:52:22 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	len_src;
	size_t	len_dst;

	len_src = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	j = 0;
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	else
	{
		while (src[j] && (len_dst + j) < dstsize - 1)
		{
			dst[len_dst + j] = src[j];
			j++;
		}
		dst[len_dst + j] = '\0';
		return (len_src + len_dst);
	}
}
