/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:21:18 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/16 16:47:11 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo "Hello $USER" | cat

int main(int ac, char **av, char **envp)
{
	t_shell	sh;

	if (ac != 1)
		return (printf("Usage: ./minishell\n"), FAILURE);
	ft_memset(&sh, 0, sizeof(t_shell));
	if (init_env(&sh.env, envp) == FAILURE)
		return (FAILURE);
	while (1)
	{
		parse(&sh);
		// init_cmd(&sh);
		ft_lstclear(&sh.tokens, free);
		//exec(&sh);
	}
}
