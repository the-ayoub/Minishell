/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:21 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/08/07 18:12:52 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_for_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	if (last_pid == -1)
		return ;
	while (waitpid_wrapper(&wpid, &status) > 0)
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

void	wrapper_single_command(t_shell *shell, t_cmd *cmd, int *pid)
{
	*pid = execute_process(shell, cmd);
	if (*pid != -1)
		wait_for_children(shell, *pid);
}
