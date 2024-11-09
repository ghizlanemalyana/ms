/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/09 19:09:45 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_received_signals = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell			sh;
	struct termios	term;

	(void)av;
	if (ac != 1/* || !isatty(0)*/)
		return (ft_putstr_fd("Usage: ./minishell\n", 2), FAILURE);
	ft_memset(&sh, 0, sizeof(t_shell));
	if (ft_export(&sh, envp) == FAILURE
		|| init_hidden_env(&sh) == FAILURE)
		return (ft_lstclear(&sh.env, free_env), FAILURE);
	set_signals_handlers();
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		parse(&sh);
		ft_lstclear(&sh.tokens, free_token);
		if (sh.cmds != NULL)
			exec(&sh);
		ft_lstclear(&sh.cmds, free_cmd);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (EXIT_SUCCESS);
}
