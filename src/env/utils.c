/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:46:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/09/25 18:57:13 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

t_env	*new_env(char *env)
{
	t_env	*new_env;
	char	*key;
	char	*value;
	int		i;

	new_env = ft_calloc(1, sizeof(t_env));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	if (key == NULL)
		return (free_env(new_env), NULL);
	i++;
	value = ft_substr(env, i, ft_strlen(env));
	if (value == NULL)
		return (free_env(new_env),NULL);
	new_env->key = key;
	new_env->value = value;
	return (new_env);
}
