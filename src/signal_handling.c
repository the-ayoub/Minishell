/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:45 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/31 21:38:44 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_in_input = 0;

void sigint_heredoc_handler(int sig)
{
    (void)sig;

    write(1, "\n", 1);
	if (g_in_input)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}

	exit(130);
}
static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_in_input)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void	setup_signal_heredoc(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigint_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell: sigaction");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}
