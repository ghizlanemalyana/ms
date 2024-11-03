/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:06:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/03 01:46:12 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_builtin(t_shell *sh, t_cmd *cmd)
{
	int			status;

	status = SUCCESS;
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		status = ft_exit(sh, cmd->argc, cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		status = ft_cd(sh, cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(sh);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		status = ft_export(sh, cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		status = ft_unset(sh, cmd->argv + 1);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(sh);
	return (status);
}

void	run_bin(t_cmd *cmd)
{
	if (cmd->argc == 0)
		exit(0);
	if (is_dir(cmd))
		exit(126);
	if (execve(cmd->argv[0], cmd->argv, cmd->envp) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		if (ft_strncmp(cmd->argv[0], "./", 2) == SUCCESS && errno == EACCES)
		{
			perror(cmd->argv[0]);
			exit(126);
		}
		else if (ft_strchr(cmd->argv[0], '/') == NULL)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
			perror(cmd->argv[0]);
		exit(127);
	}
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
		dup_stdout(&fd_out, cmd);
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
		reset_stdout(&fd_out, cmd);
	}
	sh->exit_status = status;
}

int ft_fork(t_shell *sh, t_list *node, int *pipe_fds)
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

	pid = ft_fork(sh, node, pipe_fds);
	if (pid == -1)
		return (-1);
	if (node->next)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], 0);
	}
	return (pid);
}

void	exec_bin(t_shell *sh)
{
	int		pid;
	int		pipe_fds[2];
	t_list	*cmds;

	cmds = sh->cmds;
	while (cmds)
	{
		if (cmds->next)
			pipe(pipe_fds);
		pid = ft_child(sh, cmds, pipe_fds);
		if (pid == -1)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			break ;
		}
		cmds = cmds->next;
	}
	if (sh->cmds->next)
		close(0);
	waitpid(pid, &sh->exit_status, 0);
	check_signal(sh);
	set_signals_handlers();
}

void	exec(t_shell *sh)
{
	int		stdin_fd;
	t_cmd	*cmd;

	signal(SIGINT, SIG_IGN);
	if (join_path(sh) == FAILURE)
		return ;
	cmd = sh->cmds->content;
	if (cmd->is_builtin && ft_lstsize(sh->cmds) == 1)
		exec_builtin(sh);
	else
		exec_bin(sh);
}
