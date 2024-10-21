/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/20 21:47:46 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_hidden_env(t_shell *sh)
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

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}
