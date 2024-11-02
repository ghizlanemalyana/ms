#include "../../minishell.h"

static void	close_fd(int fd)
{
	if (fd != 1 && fd != 0)
		close(fd);
}

static void	close_fds(t_cmd *cmd)
{
	close_fd(cmd->in);
	close_fd(cmd->out);
}

static int	open_fds(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == REDIR_IN)
	{
		close_fd(cmd->in);
		cmd->in = open(redir->filename, O_RDONLY);
	}
	else if (redir->type == HEREDOC)
	{
		close_fd(cmd->in);
		cmd->in = redir->fd;
	}
	else if (redir->type == REDIR_OUT)
	{
		close_fd(cmd->out);
		cmd->out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		close_fd(cmd->out);
		cmd->out = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (cmd->in == -1 || cmd->out == -1)
		return (perror("minishell: "), close_fds(cmd), FAILURE);
	return (SUCCESS);
}

int	open_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*redirs;

	cmd->in = 0;
	cmd->out = 1;
	redirs = cmd->redirs;
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type != HEREDOC && redir->filename == NULL)
			return (close_fds(cmd), ft_putstr_fd(AMBG, 2), FAILURE);
		if (open_fds(cmd, redir) == FAILURE)
			return (FAILURE);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
