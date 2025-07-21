/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/21 11:57:29 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	unvalid_var_name(char *var)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
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
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && str[i] != '=' && str[i] != '\n')
		return (0);
	return (1);
}

static int	export_no_arg(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

// TODO: protect variables
// BUG: trim
int	builtin_export(t_shell *shell, char **argv)
{
	int		i;
	int		status;
	char	*var_id;
	char	*var_value;
	char	*current;

	if (NULL == argv[1])
		return (export_no_arg(shell));
	status = 0;
	i = 1;
	while (NULL != argv[i])
	{
		var_id = ft_strtrim2(argv[i], "=");
		var_value = ft_strchr(argv[i], '=');
		if (var_value)
			*var_value++ = '\0';
		if (!is_var_name_ok(var_id))
		{
			status = unvalid_var_name(var_id);
			free(var_id);
			var_id = NULL;
			i++;
			continue ;
		}
		if (var_value)
			set_env_var(shell, var_id, var_value);
		else
		{
			current = get_env_value(shell, var_id);
			if (!current)
				set_env_var(shell, var_id, "");
		}
		free(var_id);
		i++;
	}
	return (status);
}

