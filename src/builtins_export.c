/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/23 18:59:02 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	aux_reset_loop(char *arg, int *status)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	*status = 1;
}

static int	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (shell->last_status);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	ret;
	int	i;

	if (NULL == argv[1])
		return (print_export(shell));
	i = 1;
	while (NULL != argv[i])
	{
		ret = is_valid_env_key(argv[i]);
		if (ret == FALSE)
			aux_reset_loop(argv[i], &shell->last_status);
		else if (ret == TRUE)
			update_env(shell, argv[i]);
		else
			shell->last_status = 0;
		i++;
	}
	return (shell->last_status);
}
