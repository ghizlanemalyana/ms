/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:06:05 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 00:13:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_shell *sh)
{
	t_list	*tmp;

	tmp = sh->env;
	while (tmp)
	{
		if (((t_env *)tmp->content)->value)
			printf("%s=%s\n", ((t_env *)tmp->content)->key,
				((t_env *)tmp->content)->value);
		tmp = tmp->next;
	}
}
