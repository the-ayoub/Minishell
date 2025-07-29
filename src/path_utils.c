/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:01 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/29 18:45:50 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**aux_set_paths(char **envp)
{
	char	**paths;
	char	*path_env;
	char	*path_cpy;
	int		i;

	i = 0;
	path_env = NULL;
	while (envp[i] && !path_env)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_env = envp[i] + 5;
		i++;
	}
	if (!path_env)
		return (NULL);
	path_cpy = ft_strdup(path_env);
	if (path_cpy == NULL)
		return (NULL);
	paths = ft_split(path_cpy, ':');
	free(path_cpy);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*aux_get_full_path(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (full_path != NULL)
			wrapper_strjoin(&full_path, (char *)cmd);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(const char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;

	full_path = NULL;
	paths = NULL;
	if (*cmd == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = aux_set_paths(envp);
	if (paths == NULL)
		return (NULL);
	full_path = aux_get_full_path(paths, cmd);
	if (full_path == NULL)
		free_array(paths);
	return (full_path);
}
