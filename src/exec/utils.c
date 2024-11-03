/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:15:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/03 18:53:40 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_signal(t_shell *sh)
{
	int				index;

	if (WIFEXITED(sh->exit_status))
		sh->exit_status = WEXITSTATUS(sh->exit_status);
	else if (WIFSIGNALED(sh->exit_status))
	{
		index = WTERMSIG(sh->exit_status);
		if (index == SIGINT)
		{
			ft_putchar_fd('\n', 2);
			sh->exit_status = 130;
		}
		else if (index == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			sh->exit_status = 131;
		}
	}
}

bool	is_dir(t_cmd *cmd)
{
	struct stat		st;

	if (ft_strchr(cmd->argv[0], '/') && stat(cmd->argv[0], &st) == SUCCESS)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (true);
		}
	}
	return (false);
}
