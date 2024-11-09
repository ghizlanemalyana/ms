/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:05:12 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/09 19:36:26 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	set_redir(t_shell *sh, t_cmd *cmd, t_list *node)
{
	t_list	*new;
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (redir == NULL)
		return (FAILURE);
	redir->type = ((t_token *)node->content)->type;
	if (redir->type == HEREDOC)
	{
		if (set_heredoc(sh, redir, node->next->content) == FAILURE)
			return (free(redir), FAILURE);
	}
	else if (((t_token *)node->next->content)->content != NULL)
	{
		redir->filename = ft_strdup(((t_token *)node->next->content)->content);
		if (redir->filename == NULL)
			return (free(redir), FAILURE);
	}
	new = ft_lstnew(redir);
	if (new == NULL)
		return (free(redir->filename), free(redir), FAILURE);
	ft_lstadd_back(&cmd->redirs, new);
	return (SUCCESS);
}

static int	set_cmd(t_shell *sh, t_list *tokens, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	i = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (isredir(token))
		{
			if (set_redir(sh, cmd, tokens) == FAILURE)
				return (FAILURE);
			tokens = tokens->next;
		}
		else if (token->type == ARG && token->content != NULL)
		{
			cmd->argv[i] = ft_strdup(token->content);
			if (cmd->argv[i] == NULL)
				return (FAILURE);
			i++;
		}
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (SUCCESS);
}

static int	count_argc(t_list *tokens)
{
	int		counter;
	t_token	*token;

	counter = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (isredir(token))
			tokens = tokens->next;
		else if (token->type == ARG && token->content != NULL)
			counter++;
		else if (token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (counter);
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

int	init_cmd(t_shell *sh)
{
	t_cmd	*cmd;
	t_list	*node;
	t_list	*tokens;

	tokens = sh->tokens;
	while (tokens != NULL)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL)
			return (FAILURE);
		cmd->argc = count_argc(tokens);
		cmd->argv = ft_calloc(sizeof(char *), (cmd->argc + 1));
		cmd->envp = list_to_array(sh->env);
		node = ft_lstnew(cmd);
		if (cmd->argv == NULL || cmd->envp == NULL || node == NULL
			|| set_cmd(sh, tokens, cmd) == FAILURE)
			return (free_cmd(cmd), FAILURE);
		cmd->is_builtin = is_builtin(cmd->argv[0]);
		ft_lstadd_back(&sh->cmds, node);
		while (tokens != NULL && ((t_token *)tokens->content)->type != PIPE)
			tokens = tokens->next;
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (SUCCESS);
}
