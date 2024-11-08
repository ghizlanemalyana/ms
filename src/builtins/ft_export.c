/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:08:30 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/07 20:05:29 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_env(t_list *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = (t_env *)env->content;
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		env = env->next;
	}
}

int	export(t_shell *sh, char *key, char *value, bool append)
{
	int		status;
	char	*new_key;

	if (value != NULL)
		new_key = ft_substr(key, 0, ft_strchr(key, '=') - key - append);
	else
		new_key = ft_strdup(key);
	if (new_key == NULL)
		return (FAILURE);
	if (is_key_valid(new_key) == false)
	{
		free(new_key);
		invalid_identifier("export", key);
		return (ERROR);
	}
	if (append)
		status = append_env(&sh->env, new_key, value);
	else
		status = set_env(&sh->env, new_key, value);
	free(new_key);
	return (status);
}

int	ft_export(t_shell *shell, char **av)
{
	char	*ptr;
	int		status;
	int		ret;

	ret = SUCCESS;
	if (av[0] == NULL)
		return (ft_print_env(shell->env), SUCCESS);
	while (*av)
	{
		ptr = ft_strchr(*av, '=');
		if (ptr == NULL)
			status = export(shell, *av, NULL, false);
		else if (ptr - ft_strchr(*av, '+') == 1)
			status = export(shell, *av, ptr + 1, true);
		else
			status = export(shell, *av, ptr + 1, false);
		if (status == FAILURE)
			return (FAILURE);
		if (status == ERROR)
			ret = FAILURE;
		av++;
	}
	return (ret);
}
