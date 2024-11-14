/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:49:42 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/14 02:36:07 by gmalyana         ###   ########.fr       */
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

void	free_redir(void *content)
{
	t_redir	*redir;

	redir = content;
	if (redir->heredoc_fd > 0)
		close(redir->heredoc_fd);
	free(redir->filename);
	free(redir);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	free_array(cmd->argv);
	free_array(cmd->envp);
	if (cmd->out > 2)
		close(cmd->out);
	if (cmd->in > 2)
		close(cmd->in);
	ft_lstclear(&cmd->redirs, free_redir);
	free(cmd);
}

bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	t_env	*env;
	int		i;

	array = ft_calloc(sizeof(char *), ft_lstsize(list) + 1);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		env = list->content;
		if (env->value != NULL)
		{
			array[i] = ft_strjoin(env->key, "=");
			if (array[i] == NULL)
				return (free_array(array), NULL);
			array[i] = ft_strjoin_free(array[i], env->value, 1);
			if (array[i] == NULL)
				return (free_array(array), NULL);
			i++;
		}
		list = list->next;
	}
	return (array);
}
