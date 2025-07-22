/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 21:56:50 by nimatura         ###   ########.fr       */
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



// NOTE: SYNTAX
// regex format for valid key is
// [A-Za-z_][A-Za-z0-9_]
int	is_valid_env_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isalpha(str[i]))
		i++;
	while (str[i] != '\0' && (ft_isalnum(str[i])|| str[i] == '_'))
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && str[i] != '=' && str[i] != '\n')
		return (0);
	if (i == 0)
		return (0);
	return (1);
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
	int	i;

	if (NULL == argv[1])
		return (print_export(shell));
	i = 1;
	while (NULL != argv[i])
	{
		if (is_valid_env_key(argv[i]) == 0)
			aux_reset_loop(argv[i], &shell->last_status);
		else
			update_env(shell, argv[i]);
		i++;
	}
	return (shell->last_status);
}
