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
	struct stat		path_stat;

	if (ft_strchr(cmd->argv[0], '/') && stat(cmd->argv[0], &path_stat) == SUCCESS) // ft_strchr(cmd->argv[0], '/')
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (true);
		}
	}
	return (false);
}

// void	dup_stdout(int *fd, t_cmd *cmd)
// {
// 	if (cmd->out > 2)
// 	{
// 		*fd = dup(1);
// 		dup2(cmd->out, 1);
// 		close(cmd->out);
// 	}
// }

// void	reset_stdout(int *fd, t_cmd *cmd)
// {
// 	if (cmd->out > 2)
// 	{
// 		dup2(*fd, 1);
// 		close(*fd);
// 	}
// }

void	hold_fd(int *holder, int to_hold)
{
	*holder = dup(to_hold);
}

void	reset_fd(int *holder, int stdfd)
{
	dup2(*holder, stdfd);
	close(*holder);
}
