/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:33:54 by gmalyana          #+#    #+#             */
/*   Updated: 2023/12/15 18:38:02 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_chr(long nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	l;
	long	nbr;

	nbr = n;
	l = len_chr (n);
	ptr = malloc(l + 1);
	if (!ptr)
		return (NULL);
	ptr[l] = '\0';
	l--;
	if (nbr == 0)
		ptr[0] = '0';
	if (nbr < 0)
	{
		nbr *= -1;
		ptr[0] = '-';
	}
	while (nbr > 0)
	{
		ptr[l] = nbr % 10 + 48;
		nbr /= 10;
		l--;
	}
	return (ptr);
}
