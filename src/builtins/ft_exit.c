/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:25:55 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/19 00:32:24 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int		is_valide_number(char *str)
{
	int 	i;
	size_t	num;
	int		sign;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = 2 - 1 * (str[i++] == '-');
	i = 0;
	while (ft_isdigit(str[i]) && i < 19)
		num = num * 10 + (str[i++] - '0');
	if (i == 0
		|| (num > 9223372036854775807 && sign == 1)
		|| (num > 9223372036854775807 + 1 && sign == -1))
		return (false);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

static void	clean_exit(t_shell *sh, int status)
{
	ft_lstclear(&sh->cmds, free_cmd);
	ft_lstclear(&sh->env, free_env);
	exit(status);
}

int	ft_exit(t_shell *sh, int ac, char **argv)
{
	int status;

	status = 0;
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
	clean_exit(sh, status);
	return (SUCCESS);
}
