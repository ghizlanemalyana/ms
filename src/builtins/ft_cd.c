/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:18:20 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/13 00:33:52 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*join_new_path(char *base, char *new)
{
	char		*path;
	int			base_len;
	int			new_len;

	base_len = ft_strlen(base);
	new_len = ft_strlen(new);
	path = ft_calloc(1, ft_strlen(base) + ft_strlen(new) + 2);
	if (path == NULL)
		return (NULL);
	ft_strlcat(path, base, base_len + 1);
	ft_strlcat(path, "/", base_len + 2);
	ft_strlcat(path, new, base_len + new_len + 2);
	return (path);
}

static int	update_oldpwd(t_shell *sh)
{
	char	*oldpwd;

	oldpwd = get_env(sh->hidden_env, "PWD");
	if (set_env(&sh->hidden_env, "OLDPWD", oldpwd) == FAILURE)
		return (FAILURE);
	if (is_env_exist(sh->env, "OLDPWD")
		&& set_env(&sh->env, "OLDPWD", oldpwd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	update_pwd(t_shell *sh, char *arg)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror(CDERR);
		pwd = join_new_path(get_env(sh->hidden_env, "PWD"), arg);
		if (pwd == NULL)
			return (FAILURE);
	}
	if (set_env(&sh->hidden_env, "PWD", pwd) == FAILURE)
		return (free(pwd), FAILURE);
	if (get_env(sh->env, "PWD") != NULL
		&& set_env(&sh->env, "PWD", pwd) == FAILURE)
		return (free(pwd), FAILURE);
	free(pwd);
	return (SUCCESS);
}

int	ft_cd(t_shell *sh, char **av)
{
	char	*path;

	if (av[0] == NULL)
		path = get_env(sh->env, "HOME");
	else
		path = av[0];
	if (path == NULL)
		return (printf("cd: HOME not set\n"), FAILURE);
	// free(getcwd(NULL, 0));
	if (chdir(path) == -1)
	{
		return (perror("cd"), FAILURE);
	}
	if (update_oldpwd(sh) == FAILURE
		|| update_pwd(sh, path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
