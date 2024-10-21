/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/21 01:36:15 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_received_signals = 0;

int main(int ac, char **av, char **envp)
{
	t_shell			sh;
	struct termios	term;

	if (ac != 1 || !isatty(STDIN_FILENO))
		return (printf("Usage: ./minishell\n"), FAILURE);
	ft_memset(&sh, 0, sizeof(t_shell));
	if (ft_export(&sh, envp) == FAILURE
		|| init_hidden_env(&sh) == FAILURE)
		return (ft_lstclear(&sh.env, free_env), FAILURE);
	set_signals_handlers();
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		sh.exit_status = parse(&sh);
		if (sh.exit_status != SUCCESS)
			continue ;
		// exec(&sh);
		ft_lstclear(&sh.cmds, free_cmd);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (EXIT_SUCCESS);
}
