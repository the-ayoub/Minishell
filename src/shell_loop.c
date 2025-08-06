/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:40:08 by nimatura          #+#    #+#             */
/*   Updated: 2025/08/06 17:37:45 by ohnonon          ###   ########.fr       */
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

// returns 1 in case of err, otherwise 0
// TODO: free_arr to free lnk_lst
static int	readline_wrapper(char **line, t_shell *shell)
{
	*line = readline(PROMPT);
	signignore(SIGINT);
	g_signal = 0;
	if (NULL == *line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_array(shell->env);
		return (1);
	}
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
		if (retokenize(&shell->tokens))
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
	free_cmd_list(shell->cmd);
	shell->tokens = NULL;
	shell->cmd = NULL;
}

int	shell_loop(t_shell *shell)
{
	char	*line;
	int		std_backup[2];

	while (1)
	{
		init_signals(SIG_DEF);
		if (init_std_fd(&std_backup) == 1)
			exit(1);
		signignore(SIGQUIT);
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
		reset_std_fds(std_backup, shell);
	}
	return (0);
}
