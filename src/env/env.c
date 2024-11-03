/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:00:05 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 18:48:25 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_env(t_list **list, char *key, char *value)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *list;
	while (tmp != NULL)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (value == NULL)
				return (SUCCESS);
			free(env->value);
			env->value = ft_strdup(value);
			if (env->value == NULL)
				return (FAILURE);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (create_env(list, key, value));
}

int	create_env(t_list **list, char *key, char *value)
{
	t_list	*node;
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (FAILURE);
	env->key = ft_strdup(key);
	if (env->key == NULL)
		return (free_env(env), FAILURE);
	if (value != NULL)
	{
		env->value = ft_strdup(value);
		if (env->value == NULL)
			return (free_env(env), FAILURE);
	}
	node = ft_lstnew(env);
	if (node == NULL)
		return (free_env(env), FAILURE);
	ft_lstadd_back(list, node);
	return (SUCCESS);
}

void	unset_env(t_list **list, char *key)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*env;

	tmp = *list;
	prev = NULL;
	while (tmp != NULL)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev == NULL)
				*list = tmp->next;
			else
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			ft_lstdelone(tmp, free_env);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	append_env(t_list **list, char *key, char *value)
{
	char	*old_value;
	char	*new_value;

	old_value = get_env(*list, key);
	if (old_value == NULL)
		return (create_env(list, key, value));
	new_value = ft_strjoin(old_value, value);
	if (new_value == NULL)
		return (FAILURE);
	unset_env(list, key);
	return (create_env(list, key, new_value));
}

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
