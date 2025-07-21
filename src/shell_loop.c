/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:15:37 by nimatura          #+#    #+#             */
/*   Updaked: 2025/07/09 14:04:06 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init_std_fd(int (*arr)[2])
{
	(*arr)[0] = dup(STDIN_FILENO);
	if ((*arr)[0] == -1)
		return (1);
	(*arr)[1] = dup(STDOUT_FILENO);
	if ((*arr)[1] == -1)
		return (1);
	return (0);
}

static int	aux_protect_readline(char **line, t_shell *shell)
{
	size_t	i;

	i = 0;
	while ((*line)[i] != '\0' && ft_isprint((*line)[i])
		i++;
	if (ft_isprint((*line)[i] == FALSE && (*line)[i] != '\0')
	{
		// exit sequence?
		return (1);
	}
	return (0);
}

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
	if (aux_protect_readline(line, shell) == 1)
		return (1);
	add_history(*line);
	return (0);
}

// NOTE: When do we expand variables? when we transform the token into the cmd?
// returns 1 in case of err, otherwise 0
static int	tokenize_and_check_wrp(char **line, t_shell *shell)
{
	if (*line != NULL && **line != '\0')
	{
		shell->tokens = tokenize_line(*line);
		if (syntax_check(shell->tokens))
			return (0);
		if (expand_variables(shell, shell->tokens))
			return (0);
		if (parse_tokens(shell, shell->tokens, &shell->cmd))
			return (0);
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

int	shell_loop(t_shell *shell)
{
	char	*line;
	int		std_backup[2];

	init_std_fd(&std_backup);
	setup_signal_handlers();
	while (1)
	{
		g_state.in_input = 1;
		if (0 != readline_wrapper(&line, shell))
			break ;
		if (*line)
		{
			if (tokenize_and_check_wrp(&line, shell) && shell->cmd)
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
