/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:48:54 by nimatura          #+#    #+#             */
/*   Updated: 2025/08/03 02:48:38 by ohnonon          ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <execinfo.h>
#include <unistd.h>

void print_stack_symbols_with_addr2line(void **buffer, int nptrs) 
{
	char cmd[512];
	for (int i = 0; i < nptrs; i++)
	{
		snprintf(cmd, sizeof(cmd), "addr2line -f -p -e ./minishell %p", buffer[i]);
		system(cmd);  // print directly to stdout
	}
}

void print_stack_trace(void)
{
    void *buffer[64];
    int nptrs = backtrace(buffer, 64);
    // char **symbols = backtrace_symbols(buffer, nptrs);
	print_stack_symbols_with_addr2line(buffer, nptrs);
}

void close_wrapper(int fd)
{
    if (close(fd) == -1) {
        perror("close failed");
        print_stack_trace();  // This shows where close_wrapper was called from
        assert(0 && "close_wrapper failed");
    }
}
