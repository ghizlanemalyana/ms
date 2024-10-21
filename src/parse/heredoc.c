/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:48:56 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/21 00:45:51 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_fds(int *fd)
{
	fd[WRITE_FD] = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd[READ_FD] = open("heredoc", O_RDONLY);
	unlink("heredoc");
	if (fd[WRITE_FD] == -1 || fd[READ_FD] == -1)
	{
		close(fd[WRITE_FD]);
		close(fd[READ_FD]);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	close_fds(int *fd)
{
	close(fd[WRITE_FD]);
	close(fd[READ_FD]);
}

int	put_line(t_shell *sh, int fd, char *line, bool quoted)
{
	char	*new_line;
	
	if (quoted == true)
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

int	set_heredoc(t_shell *sh, t_redir *redir, t_token *token)
{
	char	*line;
	int		stdin_fd;
	int		fds[2];

	if (open_fds(fds) == FAILURE)
		return (FAILURE);
	signal(SIGINT, heredoc_handler);
	stdin_fd = dup(STDIN_FILENO);
	redir->fd = fds[READ_FD];
	while (1)
	{
  		line = readline("> ");
		if (line == NULL || ft_strcmp(line, token->content) == 0)
		{
			free(line);
			if (g_received_signals != sh->received_signals)
				return (close_fds(fds), dup2(stdin_fd, STDIN_FILENO),
					close(stdin_fd), FAILURE);
			break;
		}
		if (put_line(sh, fds[WRITE_FD], line, token->quoted) == FAILURE)
			return (close_fds(fds), free(line), FAILURE);
		free(line);
	}
	set_signals_handlers();
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(fds[WRITE_FD]);
	return (SUCCESS);
}
