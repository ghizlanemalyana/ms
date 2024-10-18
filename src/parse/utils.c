/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:49:42 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/17 18:19:33 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->content);
	free(token);
}

void	free_cmd(void *content)
{
	int		i;
	t_cmd	*cmd;

	cmd = content;
	i = 0;
	if (cmd->argv != NULL)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
	}
	free(cmd->argv);
	free(cmd);
}
