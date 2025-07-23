/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:36:40 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/24 00:28:39 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	shell_loop(&shell);
	wrapper_free_lst(shell.raw_env);
	// free_array(shell.env);
	return (shell.last_status);
}
