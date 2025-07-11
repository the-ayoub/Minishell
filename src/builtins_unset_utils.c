/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:19:18 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/11 19:09:48 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns 1 for err cases
static int	check_var_and_del(t_list **head, char *var)
{
	if (*head == NULL || NULL == var)
		return (1);
	if (NULL == var)
		return (ft_putstr_fd("minishell: unset: missing argument\n", 2), 1);
	tmp = locate_env_var(shell->raw_env, var);
	if (NULL == tmp)
		return (0);

	return (0);
}

// Function will iter over args and delete every env var that matches its name
int	builtin_unset(t_shell *shell, char **argv)
{
	char	**new_env;
	size_t	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (check_var_and_del(&shell->raw_env, argv[i]) == 1)
			break ;
		i++;
	}
	new_env = env_compiler(shell->raw_env);
	if (NULL == new_env)
		return (ft_lstclear(&shell->raw_env, free), 1);
	free(shell->env);
	shell->env = new_env;
	return (0);
}

