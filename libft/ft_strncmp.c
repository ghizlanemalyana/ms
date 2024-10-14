/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:21:04 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/05 15:46:24 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (unsigned char)s1[i] != '\0'
		&& (unsigned char)s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	else if ((unsigned char)s1[i] - (unsigned char)s2[i] > 0)
	{
		return (1);
	}
	else if ((unsigned char)s1[i] - (unsigned char)s2[i] < 0)
	{
		return (-1);
	}
	else
		return (0);
}
