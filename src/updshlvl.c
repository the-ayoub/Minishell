/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updshlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:49:20 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 23:45:24 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_shlvl(t_shell *shell, char *argv)
{
	char	*str;
	char	*tmp;
	t_list	*new;
	int		nb;

	if (ft_strcmp(argv, "./minishell") != 0)
		return ;
	str = get_env_value(shell, "SHLVL");
	if (str == NULL)
		return ;
	nb = ft_atoi(str);
	nb += 1;
	str = ft_itoa(nb);
	tmp = ft_strjoin("SHLVL=", str);
	free(str);
	if (tmp == NULL)
		return ;
	check_var_and_del(&shell->raw_env, "SHLVL");
	free_array(shell->env);
	new = ft_lstnew(tmp);
	if (!new)
		return ;
	ft_lstadd_back(&shell->raw_env, new);
	shell->env = env_compiler(shell->raw_env);
}
