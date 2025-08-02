/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:17 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/08/01 21:31:06 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc_loop(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	redirect_heredoc(t_shell *shell, t_redir *redir)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("minishell: pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
	{
		setup_signal_heredoc();
		close(pipe_fd[0]);
		handle_heredoc_loop(pipe_fd[1], redir->file);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			shell->last_status = 130;
			close(pipe_fd[0]);
			return (-1);
		}
		return (pipe_fd[0]);
	}
}

static int	open_redirection(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_HEREDOC)
		fd = redirect_heredoc(shell, redir);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(redir->file);
	}
	return (fd);
}

int	setup_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*current;
	int		fd;

	current = cmd->redirs;
	while (current)
	{
		fd = open_redirection(current, shell);
		if (fd == -1)
			return (ERROR);
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		current = current->next;
	}
	return (SUCCESS);
}

int	reset_std_fds(int backup[2], t_shell *shell)
{
	if (backup[0] >= 0)
		if (wrapper_dup2(backup[0], STDIN_FILENO, shell) == FALSE)
			shell->last_status = errno;
	if (backup[1] >= 0)
		if (wrapper_dup2(backup[1], STDOUT_FILENO, shell) == FALSE)
			shell->last_status = errno;
	if (backup[0] >= 0)
		close(backup[0]);
	if (backup[1] >= 0)
		close(backup[1]);
	return (0);
}
