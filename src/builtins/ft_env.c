/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:06:05 by gmalyana          #+#    #+#             */
/*   Updated: 2024/09/01 21:36:23 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void	ft_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (((t_env *)tmp->content)->value)
			printf("%s=%s\n", ((t_env *)tmp->content)->key, ((t_env *)tmp->content)->value);
		tmp = tmp->next;
	}
}
 