/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:16:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 00:21:29 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_shell *shell, char **av)
{
	int	status;

	status = SUCCESS;
	while (*av)
	{
		if (is_key_valid(*av))
			unset_env(&shell->env, *av);
		else
		{
			status = FAILURE;
			invalid_identifier("unset", *av);
		}
		av++;
	}
	return (status);
}
