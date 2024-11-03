/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 01:58:46 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 00:13:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_type	get_type(char *word)
{
	if (word[0] == '|')
		return (PIPE);
	else if (word[0] == '>' && word[1] == '>')
		return (APPEND);
	else if (word[0] == '<' && word[1] == '<')
		return (HEREDOC);
	else if (word[0] == '>')
		return (REDIR_OUT);
	else if (word[0] == '<')
		return (REDIR_IN);
	else if ((word[0] == '"' && ft_strchr(word + 1, '"'))
		|| (word[0] == '\'' && ft_strchr(word + 1, '\''))
		|| (word[0] != '"' && word[0] != '\''))
		return (ARG);
	else
		return (NONE);
}

//! TODO to be updated later
static int	get_len(char *word, t_type type)
{
	int	len;

	if (type == PIPE || type == REDIR_OUT || type == REDIR_IN)
		return (1);
	else if (type == APPEND || type == HEREDOC)
		return (2);
	else
	{
		if (word[0] == '"')
			len = ft_strcspn(word + 1, "\"");
		else if (word[0] == '\'')
			len = ft_strcspn(word + 1, "'");
		else if (word[0] == '$')
		{
			if (word[1] == '?')
				return (2);
			len = 1;
			while (ft_isalnum(word[len]) || word[len] == '_')
				len++;
		}
		else
			len = ft_strcspn(word, "|>< \t\"'$");
		return (len);
	}
}

static int	add_token(t_shell *sh, t_token *new)
{
	t_list	*node;
	t_token	*last;

	if (new->expandable && expand(sh, new) == FAILURE)
		return (FAILURE);
	if (sh->tokens != NULL)
	{
		last = ft_lstlast(sh->tokens)->content; //! protection
		if (last->linked == true)
		{
			last->content = ft_strjoin_free(last->content, new->content, 1);
			if (last->content == NULL)
				return (FAILURE);
			last->linked = new->linked;
			free_token(new);
			return (SUCCESS);
		}
	}
	node = ft_lstnew(new);
	if (node == NULL)
		return (FAILURE);
	ft_lstadd_back(&sh->tokens, node);
	return (SUCCESS);
}

static bool	is_token_expandable(t_shell *sh, t_token *token)
{
	char	*content;

	if (sh->tokens != NULL
		&& ((t_token *)(ft_lstlast(sh->tokens)->content))->type == HEREDOC)
		return (false);
	content = token->content;
	while (*content != '\0')
	{
		if (is_expandable(content))
			return (true);
		content++;
	}
	return (false);
}

int	create_token(t_shell *sh, char *line, int *i)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (FAILURE);
	token->type = get_type(&line[*i]);
	if (token->type == NONE)
		return (free_token(token), ERROR);
	token->len = get_len(&line[*i], token->type);
	if (token->type == ARG)
	{
		token->quoted = (line[*i] == '"' || line[*i] == '\'');
		if (ft_strchr("|><\t ",
				*(&line[*i] + token->len + (2 * (token->quoted)))) == NULL)
			token->linked = true;
		token->content = ft_substr(line, *i + token->quoted, token->len);
		if (token->content == NULL)
			return (free_token(token), FAILURE);
		token->expandable = line[*i] != '\'' && is_token_expandable(sh, token);
	}
	*i += token->len + 2 * token->quoted;
	if (add_token(sh, token) == FAILURE)
		return (free_token(token), FAILURE);
	return (SUCCESS);
}
