/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:21 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:09:19 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_pipe_ends(int pipe_fd[2], int keep_read_end)
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (!keep_read_end && pipe_fd[0] != -1)
		close(pipe_fd[0]);
}

void	wait_for_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	if (last_pid == -1)
		return ;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_status = 128 + WTERMSIG(status);
		}
	}
}

int	builtin_in_pipe(char *cmd)
{
	const char	*pipe_builtins[] = {"echo", "env", "pwd", NULL};
	int			i;

	i = 0;
	while (pipe_builtins[i])
	{
		if (ft_strcmp(cmd, pipe_builtins[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
