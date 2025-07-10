/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:32 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:09:30 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = get_cmd_path(cmd->argv[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->argv, shell->env);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(cmd->argv[0]);
	free(path);
	exit(126);
}

void	execute_pipe(t_shell *shell, t_cmd *cmd)
{
	int		pipe_fd[2] = {-1, -1};
	int		std_backup[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	pid_t	last_pid;
	int		prev_read_end;
	pid_t	pid;

	last_pid = -1;
	prev_read_end = -1;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("minishell: pipe");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			return ;
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (prev_read_end != -1)
			{
				dup2(prev_read_end, STDIN_FILENO);
				close(prev_read_end);
			}
			if (cmd->next)
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
		if (prev_read_end != -1)
			close(prev_read_end);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_read_end = pipe_fd[0];
		}
		last_pid = pid;
		cmd = cmd->next;
	}
	if (prev_read_end != -1)
		close(prev_read_end);
	if (last_pid != -1)
	{
		wait_for_children(shell, last_pid);
	}
	reset_std_fds(std_backup);
	close(std_backup[0]);
	close(std_backup[1]);
}

pid_t	execute_process(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(shell, cmd) != SUCCESS)
			exit(1);
		if (is_builtin(cmd->argv[0]))
			exit(exec_builtin(shell, cmd));
		else
			exec_external(shell, cmd);
	}
	return (pid);
}

int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		saved_stdin;
	int		saved_stdout;

	if (!cmd)
		return (0);
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit") && cmd->next)
	{
		ft_putstr_fd("minishell: exit: pipes not allowed\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->next || !is_builtin(cmd->argv[0]) || builtin_in_pipe(cmd->argv[0]))
	{
		if (cmd->next)
			execute_pipe(shell, cmd);
		else
		{
			pid = execute_process(shell, cmd);
			if (pid != -1)
				wait_for_children(shell, pid);
		}
	}
	else
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (setup_redirections(shell, cmd) != SUCCESS)
			shell->last_status = 1;
		else
			shell->last_status = exec_builtin(shell, cmd);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	return (shell->last_status);
}
