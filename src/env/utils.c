/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/07 20:28:39 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_hidden_env(t_shell *sh)//?
{
	char	*value;

	unset_env(&sh->env, "PWD");
	unset_env(&sh->env, "OLDPWD");
	value = getcwd(NULL, 0);
	if (value == NULL)
		return (FAILURE);
	if (create_env(&sh->env, "PWD", value) == FAILURE
		|| create_env(&sh->hidden_env, "PWD", value) == FAILURE
		|| create_env(&sh->env, "OLDPWD", NULL) == FAILURE
		|| create_env(&sh->hidden_env, "OLDPWD", NULL) == FAILURE)
	{
		free(value);
		ft_lstclear(&sh->hidden_env, free_env);
		return (FAILURE);
	}
	free(value);
	return (SUCCESS);
}

bool	is_env_exist(t_list *list, char *key)
{
	t_env	*var;

	while (list != NULL)
	{
		var = list->content;
		if (ft_strcmp(var->key, key) == 0)
			return (true);
		list = list->next;
	}
	return (false);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}
