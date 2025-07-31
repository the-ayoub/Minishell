/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:04:23 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/31 19:24:43 by nimatura         ###   ########.fr       */
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

static int	aux_get_var_name(char *str, char **name)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (FALSE);
		i++;
	}
	*name = malloc(sizeof(char) * (i + 1));
	if (*name == NULL)
		return (FALSE);
	(*name)[i] = '\0';
	while (i--)
		(*name)[i] = str[i];
	return (TRUE);
}

static int	handle_new_var(t_shell *shell, char *str)
{
	char	*name;
	char	*value;

	value = ft_strchr(str, '=');
	if (value == NULL)
		return (TRUE);
	if (aux_get_var_name(str, &name) == FALSE)
		return (FALSE);
	value++;
	set_env_var(shell, name, value);
	free(name);
	return (TRUE);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int		ret;
	int		i;

	if (NULL == argv[1])
		return (print_export(shell));
	i = 1;
	while (NULL != argv[i])
	{
		ret = is_valid_env_key(argv[i]);
		if (ret == FALSE)
			aux_reset_loop(argv[i], &shell->last_status);
		else if (ret == TRUE)
			handle_new_var(shell, argv[1]);
		else
			shell->last_status = 0;
		i++;
	}
	return (shell->last_status);
}
