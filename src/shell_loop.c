/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:15:37 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/06 20:39:45 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// WARNING: OIGA QUE CHUCHA
extern int g_in_input_phase;  // Definido en signal_handling.c

// NOTE: Por qué caralho el g_in_input_phase? lo usa el readline?
// En ese caso, capaz que no hay que pasarla por referencia
// returns 1 in case of err, otherwise 0
static int	readline_wrapper(char **line, int *g_var, t_shell *shell)
{
	*line = readline(PROMPT);
	g_in_input_phase = 0;
	if (!line)
	{
		ft_putstr_fd("exit", STDOUT_FILENO);
		free_array(shell->env);
		return (1);
	}
	return (0);
}

// returns 1 in case of err, otherwise 0
static int	tokenize_and_check_wrp(char **line, t_shell *shell)
{
	if (*line != NULL && **line != '\0')
	{
		add_history(*line);
		shell->tokens = tokenize_line(*line);
		if (!syntax_check(shell->tokens))
		{
			shell->cmd = parse_tokens(shell, shell->tokens);
			if (shell->cmd)
				return (0);
		}
	}
	return (1);
}

static void	reset_cmd_line(char **line, t_shell *shell)
{
	free(line);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd);  // Libera TODA la lista de comandos
	shell->tokens = NULL;
	shell->cmd = NULL;
}

int	shell_loop(t_shell *shell)
{
	char	*line;
	int		std_backup[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	setup_signal_handlers();
	while (1)
	{
		g_in_input_phase = 1;
		if (0 != readline_wrapper(&line, &g_in_input_phase, shell))
			break ;
		if (*line)
		{
			if (0 == tokenize_and_check_wrp(&line, shell) && shell->cmd)
				execute_cmd(shell, shell->cmd);
			else
			{
				ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
				shell->last_status = 2;
			}
		}
		reset_cmd_line(&line, shell);
		//Restaurar FDs estándar después de cada comando
		reset_std_fds(std_backup);
	}
	close(std_backup[0]);
	close(std_backup[1]);
	return (0);
}
