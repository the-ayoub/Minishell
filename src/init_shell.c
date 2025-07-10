/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:40:58 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/10 20:27:56 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	generate_and_fill_arr(char ***arr, int i, t_list *lst)
{
	t_list	*node;

	node = lst;
	*arr = malloc(sizeof(char *) * (i + 1));
	if (NULL == *arr)
		return (1);
	(*arr)[i] = NULL;
	i = 0;
	while (NULL != node)
	{
		(*arr)[i] = ft_strdup((char *)node->content);
		if ((*arr)[i] == NULL)
			return (free_array(*arr), 1);
		node = node->next;
		i++;
	}
	return (0);
}

// returns the head of the list, or NULL in case of malloc err
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
			free_lst_wrp(head);
		ft_lstadd_back(&head, new);
	}
	return (head);
}

// NOTE: shell->env now with env_compiler
void	init_shell(t_shell *shell, char **envp)
{
	shell->raw_env = env_lst_init(envp);
	shell->env = env_compiler(shell->raw_env);
	print_arr(shell->env);
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
