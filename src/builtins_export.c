/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 00:00:53 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	aux_reset_loop(char **var, int *status)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(*var, STDERR_FILENO);
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

static int	set_value_name(char **var_key, char *argv)
{
	size_t	len;

	len = 0;
	if (ft_strchr(argv, '=') == NULL)
	{
		*var_key = NULL;
		return (1);
	}
	*var_key = ft_substr(argv, 0, len);
	if (*var_key == NULL)
		return (perror("Memory allocation error: set_value_name\n") , 1);
	if (FALSE == is_var_name_ok(*var_key))
	{
		free(*var_key);
		return (1);
	}
	*var_key = ft_strdup(argv);
	return (0);
}

// TODO: protect variables
int	builtin_export(t_shell *shell, char **argv)
{
	char	*tmp;
	int		i;

	if (NULL == argv[1])
		return (export_no_arg(shell));
	i = 1;
	while (NULL != argv[i])
	{
		if (is_var_name_ok(argv[i]) == 1)
			aux_reset_loop(&var_key);
		else
			update_env(shell, argv[i]);
		i++;
	}
	return (shell->last_status);
}
