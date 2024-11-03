/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:06:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 23:45:26 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_syntax(t_shell *sh)
{
	t_list	*tokens;
	t_token	*current;
	t_token	*next;

	tokens = sh->tokens;
	if (tokens == NULL)
		return (SUCCESS);
	if (tokens && ((t_token *)tokens->content)->type == PIPE)
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

static void	update_exit_status(t_shell *sh)
{
	if (g_received_signals != sh->received_signals)
	{
		sh->exit_status = 1;
		sh->received_signals = g_received_signals;
	}
}

static int	init_tokens(t_shell *sh, char *line)
{
	int		i;
	int		status;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i])
	{
		status = create_token(sh, line, &i);
		if (status != SUCCESS)
			break ;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
	}
	return (status);
}

int	parse(t_shell *sh)
{
	char	*line;
	int		status;

	line = readline(PROMPT);
	if (line == NULL)
	{
		printf("\033[F\033[2Cexit\n");
		my_exit(sh, 0);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	update_exit_status(sh);
	status = init_tokens(sh, line);
	if (status == EXIT_SUCCESS)
	{
		status = check_syntax(sh);
		if (status == SUCCESS)
			status = init_cmd(sh);
	}
	if (status == ERROR)
		ft_putstr_fd("minishell: syntax error\n", 2);
	free(line);
	ft_lstclear(&sh->tokens, free_token);
	sh->exit_status = status;
	return (status);
}
