/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:32 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/24 03:20:02 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_external(t_shell *shell, t_cmd *cmd)
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
	*b_stdin = dup(STDIN_FILENO);
	*b_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(shell, shell->cmd) != SUCCESS)
		shell->last_status = 1;
	else
		shell->last_status = exec_builtin(shell, shell->cmd);
	if (wrapper_dup2(*b_stdin, STDIN_FILENO, shell) != TRUE || \
		wrapper_dup2(*b_stdin, STDIN_FILENO, shell) != TRUE)
	{
		close(*b_stdin);
		close(*b_stdout);
		return (shell->last_status);
	}
	close(*b_stdin);
	close(*b_stdout);
	return (shell->last_status);
}

static void	wrapper_single_command(t_shell *shell, t_cmd *cmd, int *pid)
{
	*pid = execute_process(shell, cmd);
	if (*pid != -1)
		wait_for_children(shell, *pid);
}

/*int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		b_stdin;
	int		b_stdout;

	if (NULL == cmd)
		return (0);
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit") && cmd->next != NULL)
		return (\
		ft_putstr_fd("minishell: exit: pipes not allowed\n", STDERR_FILENO), 1);
	if (cmd->next || !is_builtin(cmd->argv[0]) || builtin_in_pipe(cmd->argv[0]))
	{
		if (cmd->next != NULL)
			execute_pipe(shell, cmd);
		else
			wrapper_single_command(shell, cmd, &pid);
	}
	else
		shell->last_status = exe_builtin_parent(&b_stdin, &b_stdout, shell);
	return (shell->last_status);
}*/
int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		b_stdin;
	int		b_stdout;

	if (!cmd)
		return (0);
	if (!cmd->argv || !cmd->argv[0])	//Protección: comando vacío
	{
		if (cmd->redirs) // ejecutar heredoc aunque no haya comando
			setup_redirections(shell, cmd);
		return (0);
	}
	if (!ft_strcmp(cmd->argv[0], "exit") && cmd->next != NULL)// Protección: "exit" en una tubería
	{
		ft_putstr_fd("minishell: exit: pipes not allowed\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->next || !is_builtin(cmd->argv[0]) || builtin_in_pipe(cmd->argv[0]))// Ejecutar con fork si es parte de pipe o no builtin o builtin en pipe
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


