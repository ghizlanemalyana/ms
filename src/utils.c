/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:24:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/16 17:41:20 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void	print_tokens(t_list *tokens)
{
	t_list	*node;
	t_token	*token;

	node = tokens;
	while (node)
	{
		token = node->content;
		if (token->type == ARG)
		{
			printf("\033[1;32mARG\033[0m\n");
			printf("  content: \033[1;94m%s\033[0m\n", token->content);
			if (token->linked || token->quoted || token->expandable)
			{
				printf("  status: ");
				if (token->quoted)
					printf(GREEN"quoted "RESET);
				if (token->expandable)
					printf(GREEN"expandable"RESET);
				printf("\n");
			}
		}
		else if (token->type == PIPE)
			printf("\033[0;93mPIPE\033[0m\n");
		else if (token->type == REDIR_OUT)
			printf("\033[0;95mREDIR OUT\033[0m\n");
		else if (token->type == REDIR_IN)
			printf("\033[0;95mREDIR IN\033[0m\n");
		else if (token->type == APPEND)
			printf("\033[0;96mAPPEND\033[0m\n");
		else if (token->type == HEREDOC)
			printf("\033[0;96mHEREDOC\033[0m\n");
		node = node->next;
		if (node)
			printf("\n");
	}
}

void	display_cmds(t_list *cmd)
{
	int i = 0;
	char **args;
	args = ((t_cmd *)cmd->content)->argv;
	printf("command : \n");
	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}	
}

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
	return (token->type == REDIR_OUT || token->type == REDIR_IN
		|| token->type == APPEND || token->type == HEREDOC);
}

bool	isoperator(t_token *token)
{
	return (isredir(token) || token->type == PIPE);
}
