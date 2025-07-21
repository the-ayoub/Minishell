/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:17:00 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/21 18:25:54 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	ft_check_flag(char *args, int found, int *flag)
// {
// 	int	i;
// 	int	n_flag;
//
// 	i = 1;
// 	n_flag = 1;
// 	while (args[i] && n_flag == 1)
// 	{
// 		if (args[i] != 'n' && found == 0)
// 			n_flag = 0;
// 		else if (args[i] != 'n' && found == 1)
// 			return (0);
// 		i++;
// 	}
// 	*flag = n_flag;
// 	return (n_flag);
// }

// int	ft_echo(t_pipe *p, int n_flag, int i)
// {
// 	if (p->out == -3)
// 		p->out = 1;
// 	if (!p->cmds[i])
// 	{
// 		ft_putstr_fd("\n", p->out);
// 		return (0);
// 	}
// 	while (p->cmds[i] && p->cmds[i][0] == '-' && p->cmds[i][1] != '-')
// 	{
// 		if (ft_check_flag(p->cmds[i], n_flag, &n_flag) == 1)
// 			i++;
// 		else
// 			break ;
// 	}
// 	while (p->cmds[i])
// 	{
// 		ft_putstr_fd(p->cmds[i], p->out);
// 		if (p->cmds[i + 1])
// 			ft_putstr_fd(" ", p->out);
// 		i++;
// 	}
// 	if (n_flag == 0)
// 		ft_putstr_fd("\n", p->out);
// 	return (0);
// }

// BUG:
int	builtin_echo(t_shell *shell, char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	(void)shell;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		// if (argv[i][0] == '\0')
		// {
		// 	i++;
		// 	continue;
		// }
		if (argv[1][0] != '\0' && argv[i + 1][0] != '\0')
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
