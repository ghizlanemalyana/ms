/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:25:55 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/10 15:10:02 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valide_number(char *str)
{
	int		i;
	size_t	num;
	int		sign;

	num = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
		sign = 1 - 2 * (*str++ == '-');
	i = 0;
	while (ft_isdigit(str[i]) && i < 19)
		num = num * 10 + (str[i++] - '0');
	if (i == 0
		|| (num > LONG_MAX && sign == 1)
		|| (num > (size_t)LONG_MAX + 1 && sign == -1))
		return (false);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	ft_exit(t_shell *sh, int ac, char **argv)
{
	int	status;

	printf("%d\n", sh->exit_status);
	status = sh->exit_status;
	if (ft_lstsize(sh->cmds) == 1)
		printf("exit\n");
	if (ac >= 2)
	{
		if ((is_valide_number(*argv) == false))
		{
			printf("bash: exit: %s: numeric argument required\n", *argv);
			exit(255);
		}
		status = ft_atoi(*argv);
		if (ac > 2)
		{
			printf("bash: exit: too many arguments\n");
			return (FAILURE);
		}
	}
	my_exit(sh, status);
	return (SUCCESS);
}
