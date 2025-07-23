/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:43:01 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/24 00:10:10 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	aux_iter(char **envp, int *i, char **path_env)
{
	*i = 0;
	*path_env = NULL;
	while (envp[*i] && !*path_env)
	{
		if (ft_strncmp(envp[*i], "PATH=", 5) == 0)
			*path_env = envp[*i] + 5;
		(*i)++;
	}
}

static int	aux_init_paths(char **path_cpy, char ***paths, char *p_env)
{
	*path_cpy = ft_strdup(p_env);
	*paths = ft_split(*path_cpy, ':');
	free_wrapper((void **)path_cpy);
	if (!*paths)
		return (1);
	return (0);
}

static int	aux_path_access(t_paths *p, int *i, char *cmd)
{
	while (p->paths[*i])
	{
		p->full = ft_strjoin(p->paths[*i], "/");
		if (wrapper_strjoin(&p->full, (char *)cmd))
			return (1);
		if (access(p->full, X_OK) == 0)
		{
			free_array(p->paths);
			return (0);
		}
		free(p->full);
		(*i)++;
	}
	return (1);
}

char	*get_cmd_path(const char *cmd, char **envp)
{
	t_paths path = {0};

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	aux_iter(envp, &path.i, &path.env);
	if (!path.env)
		return (NULL);
	if (aux_init_paths(&path.cpy, &path.paths, path.env) == 1)
		return (NULL);
	if (aux_path_access(&path, &path.i, (char *)cmd) == 0)
		return (path.full);
	free_array(path.paths);
	return (NULL);
}
