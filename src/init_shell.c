/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:40:58 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/08 21:42:46 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns the head of the list, or NULL in case of malloc err
// TODO: primer if, editar para considerar caso env -i
t_list	*env_lst_init(char **envp)
{
	t_list	*head;
	t_list	*new;
	char	*str;
	int			i;

	i = 0;
	if (NULL == envp)
		return (perror("init_env_data: env not valid\n"), NULL);
	str = ft_strdup(envp[i]);
	if (NULL == str)
		return (perror("env_lst_init: alloc err\n"), NULL);
	head = ft_lstnew(str);
	if (NULL == head)
		return (perror("env_lst_init: alloc err\n"), NULL);
	while (envp[++i] != NULL)
	{
		str = ft_strdup(envp[i]);
		new = ft_lstnew(str);
		if (NULL == new)
			free_lst_wrp(head);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->raw_env = env_lst_init(envp);
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
