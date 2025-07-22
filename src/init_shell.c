/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:40:58 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/22 21:45:15 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*env_lst_init(char **envp)
{
	t_list	*head;
	t_list	*new;
	char	*str;
	int		i;

	i = 0;
	if (NULL == envp)
		error_exit("No hay variables de entorno");
	str = ft_strdup(envp[i]);
	if (NULL == str)
		error_exit("env_lst_init: alloc err");
	head = ft_lstnew(str);
	if (NULL == head)
		error_exit("env_lst_init: alloc err");
	while (envp[++i] != NULL)
	{
		str = ft_strdup(envp[i]);
		new = ft_lstnew(str);
		if (NULL == new)
			wrapper_free_lst(head);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->raw_env = env_lst_init(envp);
	shell->env = env_compiler(shell->raw_env);
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
