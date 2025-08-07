/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:32 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/08/07 18:08:27 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (cmd->argv == NULL || *cmd->argv == NULL)
		exit(0);
	if (*(cmd->argv[0]) == '\0')
	{
		shell->last_status = 0;
		exit(shell->last_status);
	}
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

static int	exe_builtin_parent(int *b_stdin, int *b_stdout, t_shell *shell)
{
	if (wrapper_dup(b_stdin, STDIN_FILENO, shell) == FALSE)
		exit(shell->last_status);
	if (wrapper_dup(b_stdout, STDOUT_FILENO, shell) == FALSE)
		exit(shell->last_status);
	*b_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(shell, shell->cmd) != SUCCESS)
		shell->last_status = 1;
	else
		shell->last_status = exec_builtin(shell, shell->cmd);
	if (wrapper_dup2(*b_stdin, STDIN_FILENO, shell) != TRUE || \
		wrapper_dup2(*b_stdout, STDOUT_FILENO, shell) != TRUE)
	{
		close_wrapper(*b_stdin);
		close_wrapper(*b_stdout);
		return (shell->last_status);
	}
	close_wrapper(*b_stdin);
	close_wrapper(*b_stdout);
	return (shell->last_status);
}

// case in which there's no command other than << eof in cmdline
static int	aux_guard(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!cmd->argv || !cmd->argv[0])
	{
		if (cmd->redirs->hd_fd >= 0)
			setup_redirections(shell, cmd);
		return (FALSE);
	}
	return (TRUE);
}

int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		b_stdin;
	int		b_stdout;

	if (aux_guard(shell, cmd) == FALSE)
		return (0);
	if (!ft_strcmp(cmd->argv[0], "exit") && cmd->next != NULL)
	{
		ft_putstr_fd("minishell: exit: pipes not allowed\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->next || !is_builtin(cmd->argv[0]) || builtin_in_pipe(cmd->argv[0]))
	{
		if (cmd->next)
			execute_pipe(shell, cmd);
		else
			wrapper_single_command(shell, cmd, &pid);
	}
	else
		shell->last_status = exe_builtin_parent(&b_stdin, &b_stdout, shell);
	return (shell->last_status);
}
