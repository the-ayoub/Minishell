/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:01 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/07 16:46:14 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd_path(const char *cmd, char **envp)
{
	char	*path_env;
	char	*path_copy;
	char	*full_path;
	char	*token;
	char	**paths;
	int		i;

	path_env = NULL;
	path_copy = NULL;
	full_path = NULL;
	token = NULL;
	paths = NULL;
	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (envp[i] && !path_env)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_env = envp[i] + 5;
		i++;
	}
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	paths = ft_split(path_copy, ':');
	free(path_copy);
	if (!paths)
		return (NULL);
	for (i = 0; paths[i]; i++)
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			free_array(paths);
			return (NULL);
		}
		token = full_path;
		full_path = ft_strjoin(full_path, cmd);
		free(token);
		if (!full_path)
		{
			free_array(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_array(paths);
	return (NULL);
}
