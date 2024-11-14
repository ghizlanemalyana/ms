/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:11:50 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/14 03:29:09 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_fork(t_shell *sh, t_list *node, int *pipe_fds)
{
	int		pid;
	t_cmd	*cmd;

	cmd = node->content;
	pid = fork();
	if (pid == 0)
	{
		if (open_redirs(node->content) == FAILURE)
			exit(1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (node->next)
		{
			close(pipe_fds[0]);
			dup2(pipe_fds[1], 1);
		}
		if (cmd->out != 1)
			dup2(cmd->out, 1);
		if (cmd->in != 0)
			dup2(cmd->in, 0);
		if (cmd->is_builtin)
			exit(run_builtin(sh, node->content));
		run_bin(cmd);
	}
	return (pid);
}

int	open_child(t_shell *sh, t_list *node, int *pipe_fds)
{
	int	pid;

	if (node->next)
		pipe(pipe_fds);
	pid = ft_fork(sh, node, pipe_fds);
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (node->next)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
		close(pipe_fds[0]);
	}
	return (pid);
}

void	exec_builtin(t_shell *sh)
{
	t_cmd		*cmd;
	int			status;
	int			fd_out;

	cmd = sh->cmds->content;
	status = open_redirs(cmd);
	if (status == SUCCESS)
	{
		if (cmd->out != 2)
		{
			fd_out = dup(1);
			dup2(cmd->out, 1);
		}
		status = run_builtin(sh, sh->cmds->content);
		if (cmd->out != 2)
		{
			dup2(fd_out, 1);
			close(fd_out);
		}
	}
	sh->exit_status = status;
}

void    exec_bin(t_shell *sh)
{
    int     pid;
    int     pipe_fds[2];
    t_list  *cmds;

    cmds = sh->cmds;
    while (cmds)
    {
        pid = open_child(sh, cmds, pipe_fds);
        if (pid == -1)
        {
            sh->exit_status = 1;
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            return ;
        }
        cmds = cmds->next;
    }
    if (sh->cmds->next)
        close(0);
    waitpid(pid, &sh->exit_status, 0);
    while (wait(NULL) != -1)
        ;
    check_signal(sh);
}

void	exec(t_shell *sh)
{
	int		stdin_fd;
	t_cmd	*cmd;

	signal(SIGINT, SIG_IGN);
	if (join_path(sh) == FAILURE)
		return ;
	cmd = sh->cmds->content;
	if (ft_lstsize(sh->cmds) > 1)
		stdin_fd = dup(0);
	if (cmd->is_builtin && ft_lstsize(sh->cmds) == 1)
		exec_builtin(sh);
	else
		exec_bin(sh);
	if (ft_lstsize(sh->cmds) > 1)
	{
		dup2(stdin_fd, 0);
		close(stdin_fd);
	}
	signal(SIGINT, sigint_handler);
}
