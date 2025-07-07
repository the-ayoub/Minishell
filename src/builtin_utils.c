/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:37:17 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 16:47:02 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(shell, cmd->argv));
	return (0);
}
int	is_valid_identifier(char *str)
{
	if (!str || !*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
