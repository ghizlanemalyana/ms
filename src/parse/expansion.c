/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:19:08 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/14 02:16:56 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_expandable(char *line)
{
	if (*line == '$')
	{
		if (ft_isalpha(*(line + 1)) || *(line + 1) == '_' || *(line + 1) == '?')
			return (true);
	}
	return (false);
}

int	count_var_len(char *str)
{
	int	i;

	if (*(str + 1) == '?')
		return (2);
	else
	{
		i = 1;
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	}
	return (i);
}

char	*expand_env(t_shell *sh, char *line, int len)
{
	char	*key;
	char	*str;

	if (*line == '?')
		return (ft_itoa(sh->exit_status));
	key = ft_substr(line, 0, len);
	if (key == NULL)
		return (NULL);
	str = get_env(sh->env, key);
	free(key);
	if (str == NULL)
		str = ft_strdup("");
	else
		str = ft_strdup(str);
	return (str);
}

char	*expand_string(t_shell *sh, char *line)
{
	char	*new;
	char	*str;
	size_t	len;

	new = NULL;
	while (*line != '\0')
	{
		if (is_expandable(line))
		{
			len = count_var_len(line);
			str = expand_env(sh, line + 1, len - 1);
		}
		else
		{
			len = ft_strcspn(line + (*line == '$'), "$");
			str = ft_substr(line, 0, len);
		}
		if (str == NULL)
			return (free(new), NULL);
		new = ft_strjoin_free(new, str, 3);
		if (new == NULL)
			return (NULL);
		line = line + len;
	}
	return (new);
}

int	expand(t_shell *sh, t_token *token)
{
	char	*ptr;

	ptr = token->content;
	if (token->quoted)
		token->content = expand_string(sh, token->content);
	else
	{
		if (token->content[1] == '?')
			token->content = ft_itoa(sh->exit_status);
		else
		{
			token->content = get_env(sh->env, token->content + 1);
			if (token->content == NULL)
				return (free(ptr), SUCCESS);
			token->content = ft_strdup(token->content);
		}
	}
	free(ptr);
	if (token->content == NULL)
		return (FAILURE);
	return (SUCCESS);
}
