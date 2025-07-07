/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:40:58 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:10:10 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = copy_env(envp);
	if (!shell->env)
		error_exit("Error: fallo al copiar el entorno");
	if (isatty(STDIN_FILENO))
	{
		shell->interactive = 1;
		if (tcgetattr(STDIN_FILENO, &shell->orig_termios) == -1)
			error_exit("Error: tcgetattr falló");
	}
	else
		shell->interactive = 0;
	shell->last_status = 0;
	shell->cmd = NULL;
	shell->tokens = NULL;
}
