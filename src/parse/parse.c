/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:06:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/16 22:49:35 by gmalyana         ###   ########.fr       */
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
	else if (word[0] == '"' && ft_strchr(word + 1, '"')
		|| word[0] == '\'' && ft_strchr(word + 1, '\'')
		|| (word[0] != '"' && word[0] != '\''))
		return (ARG);
	else
		return (NONE);
}

//TODO to be updated later
int	get_len(char *word, t_type type)
{
	int len = 0;

	if (type == PIPE || type == REDIR_OUT || type == REDIR_IN)
		return (1);
	else if (type == APPEND || type == HEREDOC)
		return (2);
	else
	{
		if (word[0] == '"')
			len = strcspn(word + 1, "\"");
		else if (word[0] == '\'')
			len = strcspn(word + 1, "'");
		else if (word[0] == '$')
		{
			if (word[1] == '?')
				return (2);
			len = 1;
			while (ft_isalnum(word[len]) || word[len] == '_')
				len++;
		}
		else
			len = strcspn(word, "|>< \t\"'$");
		return (len);
	}
}

int	add_token(t_shell *sh, t_token *new)
{
	t_list	*node;
	char	*tmp;
	t_token	*last;

	if (sh->tokens != NULL)
	{
		last = ft_lstlast(sh->tokens)->content;
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
	if (new->expandable && expand(sh, new) == FAILURE)
		return (FAILURE);
	node = ft_lstnew(new);
	if (node == NULL)
		return (FAILURE);
	ft_lstadd_back(&sh->tokens, node);
	return(SUCCESS);
}

static bool	is_token_expandable(t_shell *sh, t_token *token)
{
	char	*content;

	if (sh->tokens != NULL
		&& ((t_token *)(ft_lstlast(sh->tokens)->content))->type == HEREDOC)
		return (false);
	content = token->content;
	while(*content != '\0')
	{
		if (is_expandable(content))
			return (true);
		content++;
	}
	return (false);
}

int create_token(t_shell *sh, char *line, int *i)
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
		if (ft_strchr("|><\t ", *(&line[*i] + token->len + (2 * (token->quoted)))) == NULL)
			token->linked = true;
		token->content = ft_substr(line, *i + token->quoted, token->len);
		if (token->content == NULL)
			return (free_token(token), FAILURE);
		token->expandable = line[*i] != '\'' && is_token_expandable(sh, token);
	}
	*i += token->len + 2 * token->quoted;
	add_token(sh, token);
	return (SUCCESS);
}

int check_syntax(t_shell *sh)
{
	t_list	*tokens;
	t_token	*current;
	t_token	*next;
	
	tokens = sh->tokens;
	//! Check if tokens aren't NULL
	if (((t_token *)tokens->content)->type == PIPE)
		return (ERROR);
	if (isoperator(ft_lstlast(tokens)->content))
			return (ERROR);
	while (tokens->next != NULL)
	{
	 	current = tokens->content;
		next = tokens->next->content;
		if (isredir(current) && isoperator(next))
			return (ERROR);
		if (current->type == PIPE && next->type == PIPE)
			return (ERROR);
		tokens = tokens->next;
	}
	return (SUCCESS);
}
int	parse(t_shell *sh)
{
	char	*line;
	int		i;

	i = 0;
	line = readline(PROMPT);
	if (line == NULL)
		exit(0);
	while (line[i] && line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (create_token(sh, line, &i) != SUCCESS)
			exit(1);
		while (line[i] && line[i] == ' ' || line[i] == '\t')
			i++;
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	free(line);
	sh->exit_status = check_syntax(sh);
	print_tokens(sh->tokens);
	return (SUCCESS);
}
