/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:48:54 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/29 18:22:00 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_wrapper(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int	waitpid_wrapper(pid_t *ptr, int *status)
{
	*ptr = waitpid(-1, status, 0);
	return (*ptr);
}
