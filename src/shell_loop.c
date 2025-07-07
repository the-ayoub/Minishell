/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:30 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:11:05 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	shell_loop(t_shell *shell)
{
	char	*line;
	int		std_backup[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	setup_signal_handlers();
	while (1)
	{
		g_state.in_input = 1;
		line = readline(PROMPT);
		g_state.in_input = 0;
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free_array(shell->env);
			break ;
		}
		if (*line)
		{
			add_history(line);
			shell->tokens = tokenize_line(line);
			if (!syntax_check(shell->tokens))
			{
				shell->cmd = parse_tokens(shell, shell->tokens);
				if (shell->cmd)
					execute_cmd(shell, shell->cmd);
			}
			else
			{
				ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
				shell->last_status = 2;
			}
		}
		free(line);
		free_tokens(shell->tokens);
		free_cmd_list(shell->cmd);
		shell->cmd = NULL;
		reset_std_fds(std_backup);
	}
	close(std_backup[0]);
	close(std_backup[1]);
	return (0);
}
