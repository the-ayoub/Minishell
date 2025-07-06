/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:07:05 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/06 20:07:11 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
    shell->env = copy_env(envp);
    if (!shell->env)
        error_exit("Error: fallo al copiar el entorno");
    if(isatty(STDIN_FILENO))
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
