/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:19:18 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/10 21:32:07 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_check_arg(char **str, t_shell *shell, char *var)
{
	char	*tmp;

	if (NULL == var)
		return (ft_putstr_fd("minishell: unset: missing argument\n", 2), 1);
	tmp = locate_env_var(shell->raw_env, var);
	if (NULL == tmp)
		return (0);

	return (0);
}

// check if the argv is a valid variable
// locate the variable
// free the content
// delete the node
int	builtin_unset(t_shell *shell, char **argv)
{
	size_t	i;
	char	*str;

	i = 1;
	while (argv[i] != NULL)
	{
		str = locate_env_var(shell->raw_env, argv[i]);
		if (NULL == str)
			return (0);

	}
	shell->env = env_compiler(shell->raw_env);
	return (0);
}

