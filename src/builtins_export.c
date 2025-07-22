/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 21:47:27 by nimatura         ###   ########.fr       */
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

int	is_var_name_ok(char *str)
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

static int	update_env(t_shell *shell, char *arg)
{
	char	*var;
	t_list	*node;

	var = ft_strdup(arg);
	if (NULL != var)
	{
		node = ft_lstnew(var);
		if (node != NULL)
		{
			ft_lstadd_back(&shell->raw_env, node);
			free_array(shell->env);
			shell->env = env_compiler(shell->raw_env);
		}
		else
		{
			shell->last_status = 1;
			free(var);
		}
	}
	else
		shell->last_status = 1;
	return (shell->last_status);
}

// BUG: is_var_name_ok
// Accepts only numbers
int	builtin_export(t_shell *shell, char **argv)
{
	int	i;

	if (NULL == argv[1])
		return (print_export(shell));
	i = 1;
	while (NULL != argv[i])
	{
		if (is_var_name_ok(argv[i]) == 0)
			aux_reset_loop(argv[i], &shell->last_status);
		else
			update_env(shell, argv[i]);
		i++;
	}
	return (shell->last_status);
}
