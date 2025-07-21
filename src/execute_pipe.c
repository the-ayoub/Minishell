/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:38:09 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/21 23:00:12 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

typedef struct	s_pipe
{
	int		pipe_fd[2];
	int		b_std[2];
	pid_t	last_pid;
	int		prev_read_end;
	pid_t	pid;
}			t_pipe;

// proteger
static void	fork_wrapper(t_shell *shell, t_pipe *data)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->prev_read_end != -1)
		{
			dup2(data->prev_read_end, STDIN_FILENO);
			close(data->prev_read_end);
		}
		if (shell->cmd->next)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		if (setup_redirections(shell, cmd) != SUCCESS)
			exit(1);
		if (is_builtin(cmd->argv[0]))
			exit(exec_builtin(shell, cmd));
		else
			exec_external(shell, cmd);
	}
	return ();
}

static void	set_pipe_data(t_pipe *data)
{
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->b_std[0] = dup(STDIN_FILENO);
	data->b_std[1] = dup(STDOUT_FILENO);
	data->last_pid = - 1;
	data->prev_read_end = - 1;


}

void	execute_pipe(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*cmd_iter;
	t_pipe	data;

	set_pipe_data(&data);
	cmd_iter = cmd;
	while (cmd_iter)
	{
		if (cmd_iter->next)
		{
			if (pipe(data.pipe_fd) == -1)
			{
				perror("minishell: pipe");
				return ;
			}
		}
		fork_wrapper(shell, &data);
		if (data.prev_read_end != -1)
			close(data.prev_read_end);
		if (cmd_iter->next)
		{
			close(data.pipe_fd[1]);
			data.prev_read_end = data.pipe_fd[0];
		}
		data.last_pid = data.pid;
		cmd_iter = cmd_iter->next;
	}
	if (data.prev_read_end != -1)
		close(data.prev_read_end);
	if (data.last_pid != -1)
		wait_for_children(shell, data.last_pid);
	reset_std_fds(&*data.b_std);
	close(data.b_std[0]);
	close(data.b_std[1]);
}

