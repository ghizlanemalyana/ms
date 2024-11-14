/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:24:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/14 00:49:33 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*ptr;

	ptr = ft_strjoin(s1, s2);
	if (to_free == 1)
		free(s1);
	else if (to_free == 2)
		free(s2);
	else if (to_free == 3)
	{
		free(s1);
		free(s2);
	}
	return (ptr);
}

bool	isredir(t_token *token)
{
	return (token->type == REDIR_OUT
		|| token->type == REDIR_IN
		|| token->type == APPEND
		|| token->type == HEREDOC);
}

bool	isoperator(t_token *token)
{
	return (isredir(token) || token->type == PIPE);
}

void	my_exit(t_shell *sh, int status)
{
	ft_lstclear(&sh->cmds, free_cmd);
	ft_lstclear(&sh->env, free_env);
	ft_lstclear(&sh->hidden_env, free_env);
	rl_clear_history();
	exit(status);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
