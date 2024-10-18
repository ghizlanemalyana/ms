/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:15:56 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/18 23:19:43 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

//! To be updated
int	ft_pwd(t_shell *sh)
{
	char *str = getcwd(NULL, 0);
	if (str == NULL)
	{
		perror("minishell : ");
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (SUCCESS);
}
