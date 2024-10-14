/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:25:55 by gmalyana          #+#    #+#             */
/*   Updated: 2024/08/30 21:30:23 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int		is_valide_number(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) == 1)
		i++;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] != '\0')
		return 0;
	return 1;
}

int	ft_exit(int ac, char **argv)
{
	int num;

	if (ac == 2)
	{
		if ((is_valide_number(argv[1]) == 0) || (ft_strlen(argv[1]) > 19))
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
		num = ft_atoi(argv[1]); 
		printf("exit\n");
		exit(num);
	}
	else if (ac > 2)
	{
		if (is_valide_number(argv[1]) == 0)
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", argv[1]);
			exit(255);
		}
		printf("exit\nbash: exit: too many arguments\n");
		return (1);
	}
	exit(0);
}