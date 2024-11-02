# include "../../minishell.h"

static int	set_path(char **paths, t_cmd *cmd)
{
	int			i;
	int			path_len;
	int			cmd_len;
	char		*ptr;

	if (cmd->is_builtin || cmd->argc == 0
		|| **cmd->argv == '/' || **cmd->argv == '.')
		return (SUCCESS);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		cmd_len = ft_strlen(cmd->argv[0]);
		ptr = ft_calloc(path_len + cmd_len + 2, sizeof(char));
		if (ptr == NULL)
			return (FAILURE);
		ft_strlcat(ptr, paths[i], path_len + 1);
		ft_strlcat(ptr, "/", path_len + 2);
		ft_strlcat(ptr, cmd->argv[0], path_len + cmd_len + 2);
		if (access(ptr, X_OK) == 0)
			return (free(cmd->argv[0]), cmd->argv[0] = ptr, SUCCESS);
		free(ptr);
		i++;
	}
	return (SUCCESS);
}

int	join_path(t_shell *sh)
{
	char	**paths;
	char	*path;
	int		ret;
	t_list	*cmds;

	path = get_env(sh->env, "PATH");
	if (path == NULL)
		return (SUCCESS);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (FAILURE);
	if (*paths == NULL)
		return (free(paths), SUCCESS);
	cmds = sh->cmds;
	while (cmds)
	{
		ret = set_path(paths, cmds->content);
		if (ret == FAILURE)
			break ;
		cmds = cmds->next;
	}
	free_array(paths);
	return (ret);
}
