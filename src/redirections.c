/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:17 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:10:56 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_heredoc(t_shell *shell, t_redir *redir)
{
	int		fd[2];
	char	*line;

	(void)shell;
	if (!redir || !redir->file)
	{
		ft_putstr_fd("minishell: heredoc: missing delimiter\n", STDERR_FILENO);
		return (-1);
	}
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd[1]);
	return (fd[0]);
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

int	reset_std_fds(int backup[2])
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	return (0);
}
