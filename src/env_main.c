/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:38:32 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/22 21:35:53 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	generate_and_fill_arr(char ***arr, int i, t_list *lst)
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

char	**env_compiler(t_list *head)
{
	char	**arr;
	t_list	*iter;
	int		i;

	iter = head;
	i = 0;
	while (iter != NULL)
	{
		iter = iter->next;
		i++;
	}
	arr = NULL;
	if (1 == generate_and_fill_arr(&arr, i, head))
		return (wrapper_free_lst(head), NULL);
	return (arr);
}

char	*get_env_value(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// TODO: set_env_var deberia modificar la lista en variable shell->raw_env
// y despues compilar, no al revés
void set_env_var(t_shell *shell, const char *name, const char *value)
{
	char *var;
	int i = 0;
	int len = ft_strlen(name);

	// Crear la variable en formato "nombre=valor"
	var = ft_strjoin(name, "=");
	char *temp = var;
	var = ft_strjoin(var, value);
	free(temp);

	// Buscar si la variable ya existe
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = var;
			return;
		}
		i++;
	}

	// Agregar nueva variable al final
	char **new_env = malloc((i + 2) * sizeof(char *));
	for (int j = 0; j < i; j++) {
		new_env[j] = shell->env[j];
	}
	new_env[i] = var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}
