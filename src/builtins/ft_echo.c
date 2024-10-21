/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:06:07 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/21 00:58:38 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **argv)
{
	int		i;
	bool	n_flag;

	n_flag = true;
	while (*argv)
	{
		if (ft_strncmp(*argv, "-n", 2) == 0
			&& ft_strlen(*argv) - 1 == ft_strspn(&argv[0][1], "n"))
			n_flag = false;
		else
			break ;
		argv++;
	}
	while (*argv)
	{
		printf("%s", *argv);
		if (*(argv + 1))
			printf(" ");
		argv++;
	}
	if (n_flag)
		printf("\n");
}
