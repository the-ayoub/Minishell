/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:15:37 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/08 00:30:11 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns 1 in case of err, otherwise 0
// TODO: free_arr to free lnk_lst
static int	readline_wrapper(char **line, t_shell *shell)
{
	*line = readline(PROMPT);
	g_state.in_input = 0;
	if (NULL == *line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
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
	free(*line);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd);  // Libera TODA la lista de comandos
	shell->tokens = NULL;
	shell->cmd = NULL;
}

// TODO: proteger dup
int	shell_loop(t_shell *shell)
{
	char	*line;
	int		std_backup[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	setup_signal_handlers();
	while (1)
	{
		g_state.in_input = 1;
		if (0 != readline_wrapper(&line, shell))
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
		reset_std_fds(std_backup); //Restaurar FDs estándar después de cada comando
	}
	close(std_backup[0]);
	close(std_backup[1]);
	return (0);
}
