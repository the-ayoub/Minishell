/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/11 21:09:17 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	builtin_export(t_shell *shell, char **argv)
{
	int		i;
	int		status;
	char	*name;
	char	*value;
	char	*current;

	status = 0;
	if (!argv[1])
		return (export_no_arg(shell));
	i = 1;
	while (argv[i])
	{
		name = argv[i];
		value = ft_strchr(argv[i], '=');
		if (value)
			*value++ = '\0';
		if (!is_valid_identifier(name))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
			i++;
			continue ;
		}
		if (value)
			set_env_var(shell, name, value);
		else
		{
			current = get_env_value(shell, name);
			if (!current)
				set_env_var(shell, name, "");
		}
		i++;
	}
	return (status);
}

