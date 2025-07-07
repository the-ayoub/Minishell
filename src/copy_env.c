/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:38:32 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 20:08:37 by aybelhaj         ###   ########.fr       */
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

char	*get_env_value(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	set_env_var(t_shell *shell, const char *name, const char *value)
{
	char	*var;
	char	*temp;
	int		i;
	int		len;
	int		j;
	char	**new_env;

	i = 0;
	len = ft_strlen(name);
	var = ft_strjoin(name, "=");
	temp = var;
	var = ft_strjoin(var, value);
	free(temp);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = var;
			return ;
		}
		i++;
	}
	new_env = malloc((i + 2) * sizeof(char *));
	j = 0;
	while (j < i)
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[i] = var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}
