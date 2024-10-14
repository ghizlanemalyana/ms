/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:10:26 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/14 23:20:52 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*m;
	int		i;
	int		len;

	m = (char *)s;
	len = ft_strlen(s);
	i = len - 1;
	while (i >= 0)
	{
		if (m[i] == (char)c)
		{
			return (&m[i]);
		}
		i--;
	}
	if ((char)c == '\0')
	{
		return (m + len);
	}
	return (NULL);
}
