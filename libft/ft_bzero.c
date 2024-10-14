/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:26:45 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/12 14:22:02 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*mem;
	unsigned char	c;
	size_t			i;

	mem = s;
	c = '\0';
	i = 0;
	while (i < n)
	{
		mem[i] = c;
		i++;
	}
}
