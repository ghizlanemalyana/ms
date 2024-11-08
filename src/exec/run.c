/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:29:06 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/06 18:35:07 by gmalyana         ###   ########.fr       */
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
		ft_pwd();
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
