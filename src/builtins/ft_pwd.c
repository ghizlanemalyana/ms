/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:15:56 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/20 23:19:02 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int	ft_pwd(t_shell *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
