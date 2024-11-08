/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:48:56 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/07 16:39:50 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_fds(int *fds)
{
	if (fds[WRITE_FD] != -1)
		close(fds[WRITE_FD]);
	if (fds[READ_FD] != -1)
		close(fds[READ_FD]);
}

static int	open_fds(int *fds)
{
	fds[WRITE_FD] = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fds[READ_FD] = open("heredoc", O_RDONLY);
	unlink("heredoc");
	if (fds[WRITE_FD] == -1 || fds[READ_FD] == -1)
		return (close_fds(fds), FAILURE);
	return (SUCCESS);
}

static int	put_line(t_shell *sh, int fd, char *line, bool quoted)
{
	char	*new_line;

	if (quoted == true || ft_strlen(line) == 0)
		ft_putendl_fd(line, fd);
	else
	{
		new_line = expand_string(sh, line);
		if (new_line == NULL)
			return (FAILURE);
		ft_putendl_fd(new_line, fd);
		free(new_line);
	}
	return (SUCCESS);
}

static int	open_heredoc(t_shell *sh, t_token *token, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			if (g_received_signals != sh->received_signals)
				return (FAILURE);
			break ;
		}
		if (put_line(sh, write_fd, line, token->quoted) == FAILURE)
			return (free(line), FAILURE);
		free(line);
	}
	return (SUCCESS);
}

int	set_heredoc(t_shell *sh, t_redir *redir, t_token *token)
{
	int		status;
	int		stdin_fd;
	int		fds[2];

	if (open_fds(fds) == FAILURE)
		return (FAILURE);
	signal(SIGINT, heredoc_handler);
	stdin_fd = dup(STDIN_FILENO);
	redir->fd = fds[READ_FD];
	status = open_heredoc(sh, token, fds[WRITE_FD]);
	if (status == FAILURE)
		close(fds[READ_FD]);
	set_signals_handlers();
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(fds[WRITE_FD]);
	return (status);
}
