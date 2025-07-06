/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:15:37 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/06 20:17:10 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_in_input_phase;  // Definido en signal_handling.c

int shell_loop(t_shell *shell)
{
	char *line;
	int std_backup[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	setup_signal_handlers();
	while (1)
	{
		g_in_input_phase = 1;
		line = readline(PROMPT);
		g_in_input_phase = 0;
		if (!line)
		{
			ft_putstr_fd("exit", STDOUT_FILENO);
			free_array(shell->env);
			break; 
		}
		if (*line) 
		{
			add_history(line);
			shell->tokens = tokenize_line(line);
			if (!syntax_check(shell->tokens)) {
				shell->cmd = parse_tokens(shell, shell->tokens);
				if (shell->cmd)
					execute_cmd(shell, shell->cmd);
			} else {
				ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
				shell->last_status = 2;
			}
		}
		free(line);
		free_tokens(shell->tokens);
		free_cmd_list(shell->cmd);  // Libera TODA la lista de comandos
		shell->tokens = NULL;
		shell->cmd = NULL;

		//Restaurar FDs estándar después de cada comando
		reset_std_fds(std_backup);
	}
	close(std_backup[0]);
	close(std_backup[1]);
	return (0);
}
