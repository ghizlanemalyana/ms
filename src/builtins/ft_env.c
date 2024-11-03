/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:10:16 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 18:10:17 by gmalyana         ###   ########.fr       */
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
