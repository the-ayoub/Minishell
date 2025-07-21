/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:03:22 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 00:13:14 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wrapper_dup2(int oldfd, int newfd, t_shell *shell)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		shell->last_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	wrapper_dup(int *holder, int fd, t_shell *shell)
{
	*holder = dup(fd);
	if (*holder == -1)
	{
		perror("dup failed");
		shell->last_status = 1;
		return (FALSE);
	}
	return (TRUE);
}
