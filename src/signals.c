/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:24:39 by gmalyana          #+#    #+#             */
/*   Updated: 2024/11/09 19:23:06 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_handler(int sig)
{
	(void)sig;
	g_received_signals++;
	close(0);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_received_signals++;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_handlers(void)
{
	// rl_catch_signals = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
