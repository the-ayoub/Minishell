/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deprecated.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:29:49 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/18 19:06:02 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**copy_envp;

	i = 0;
	while (envp[i])
		i++;
	copy_envp = malloc((i + 1) * sizeof(char *));
	if (!copy_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy_envp[i] = ft_strdup(envp[i]);
		if (!copy_envp[i])
		{
			free_array(copy_envp);
			return (NULL);
		}
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}

// Not needed in expansion.c, absolutely no clue on what does this do
void	expand_exit_status(t_shell *shell, char **result)
{
	char	*exit_str;
	char	*new_result;

	exit_str = ft_itoa(shell->last_status);
	new_result = ft_strjoin(*result, exit_str);
	free(*result);
	free(exit_str);
	*result = new_result;
}
