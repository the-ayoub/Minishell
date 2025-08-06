/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:17 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/08/06 20:02:02 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

static int	open_redirection(t_redir *redir)
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
		fd = redir->hd_fd;
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
		fd = open_redirection(current);
		if (fd == -1)
			return (ERROR);
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
		{
			if (wrapper_dup2(fd, STDIN_FILENO, shell) == FALSE)
				ft_putstr_fd("STDIN_FILENO err\n", 2);
		}
		else if (wrapper_dup2(fd, STDOUT_FILENO, shell) == FALSE)
				ft_putstr_fd("STDOUT err\n", 2);
		close_wrapper(fd);
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
		close_wrapper(backup[0]);
	if (backup[1] >= 0)
		close_wrapper(backup[1]);
	return (0);
}
