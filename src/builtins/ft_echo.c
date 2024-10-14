/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:06:07 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/29 21:01:29 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **argv)
{
	int i = 0;
	if ((argv[0][i] == '-' && argv[0][i+1] == 'n' && (strlen(&argv[0][1]) == strspn(&argv[0][1], "n"))))
	{
		i = 1;
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else
	{
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			printf(" ");
			if (argv[i + 1] == NULL)
				printf("\n");
			i++;
		}
	}
}