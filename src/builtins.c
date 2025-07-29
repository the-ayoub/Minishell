/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:38:11 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/29 18:53:12 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_exit_arg(char *arg)
{
	if (!arg || *arg == '\0')
		return (0);
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	int	exit_code;

	exit_code = 0;
	(void)shell;
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (argv[1] && !is_valid_exit_arg(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	else if (argv[1])
	{
		exit_code = ft_atoi(argv[1]);
	}
	exit(exit_code);
}

int	builtin_pwd(t_shell *shell, char **argv)
{
	char	*cwd;

	(void)argv;
	(void)shell;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

int	builtin_env(t_shell *shell, char **argv)
{
	(void)argv;
	print_lst(shell->raw_env);
	return (0);
}
