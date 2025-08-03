/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:18:53 by nimatura          #+#    #+#             */
/*   Updated: 2025/08/03 02:31:39 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_heredoc_fd(void)
{
	int	tty_fd;

	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd != -1)
	{
		if (dup2(tty_fd, STDIN_FILENO) == -1)
			ft_putstr_fd("can't restore fd term\n",
				STDERR_FILENO);
		close_wrapper(tty_fd);
	}
}

static int	readline_loop(char **line, char **result, char *delim)
{
	while (1)
	{
		*line = readline("> ");
		if (!*line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by EOF\n",
				STDERR_FILENO);
			return (FALSE);
		}
		if (ft_strcmp(*line, delim) == 0)
		{
			free_wrapper((void **)line);
			free_wrapper((void **)result);
			break ;
		}
		if (wrapper_strjoin(result, *line) == FALSE)
			break ;
		free_wrapper((void **)line);
	}
	return (TRUE);
}

int	handle_heredoc_loop(int fd, const char *delimiter)
{
	char	*line;
	char	*result;

	result = NULL;
	set_heredoc_fd();
	if (readline_loop(&line, &result, (char *)delimiter) == FALSE)
	{
		free_wrapper((void **)line);
		free_wrapper((void **)result);
		close_wrapper(fd);
		return (0);
	}
	if (result != NULL)
	{
		write(fd, result, ft_strlen(result));
		write(fd, "\n", 1);
	}
	free_wrapper((void **)&result);
	close_wrapper(fd);
	return (0);
}

static void	heredoc_fork(int *pid, int *fd, char *delim)
{
	int	status;

	*pid = fork();
	if (*pid == -1)
		exit(130);
	if (*pid == 0)
	{
		close_wrapper(fd[0]);
		handle_heredoc_loop(fd[1], delim);
		close_wrapper(fd[1]);
		exit(0);
	}
	else
	{
		close_wrapper(fd[1]);
		waitpid(*pid, &status, 0);
		exit(0);
	}
}

int	redirect_heredoc(t_shell *shell, t_redir *redir)
{
	int	fd[2];
	int	pid;

	(void)shell;
	if (NULL == redir || NULL == redir->file)
	{
		ft_putstr_fd("minishell: heredoc: missing delimiter\n", STDERR_FILENO);
		return (-1);
	}
	if (pipe(fd) == -1)
		return (-1);
	heredoc_fork(&pid, fd, redir->file);
	return (fd[0]);
}
