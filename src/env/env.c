/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:00:05 by gmalyana          #+#    #+#             */
/*   Updated: 2024/09/25 19:19:27 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(t_list *list, char *key)
{
	t_env	*var;

	while (list != NULL)
	{
		var = list->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var->value);
		list = list->next;
	}
	return (NULL);
}

int init_env(t_list **list, char **envp)
{
	t_list	*node;
	t_env	*env;
	int 	i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		env = new_env(envp[i]);
		if (env == NULL)
			return (FAILURE);
		node = ft_lstnew(env);
		if (node == NULL)
			return (free_env(env), FAILURE);
		ft_lstadd_back(list, node);
		i++;
	}
	return (SUCCESS);
}
