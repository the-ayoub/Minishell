/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:06:41 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/28 19:38:25 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_env(t_shell *shell, char *arg)
{
	char	*var;
	t_list	*node;

	var = ft_strdup(arg);
	if (NULL != var)
	{
		node = ft_lstnew(var);
		if (node != NULL)
		{
			ft_lstadd_back(&shell->raw_env, node);
			free_array(shell->env);
			shell->env = env_compiler(shell->raw_env);
		}
		else
		{
			shell->last_status = 0;
			free(var);
		}
	}
	else
		shell->last_status = 0;
	return (shell->last_status);
}

static int	is_var_name_ok(char c)
{
	if (c == '?')
		return (TRUE);
	if (c == ' ' || c == '\t' || c == '\0' || c == '$')
		return (FALSE);
	if (c == '\'' || c == '"' || c == '/')
		return (FALSE);
	return (TRUE);
}

// NOTE: SYNTAX
// regex format for valid key is
// [A-Za-z_][A-Za-z0-9_]
int	is_valid_env_key(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[i] == '\0')
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
	if (str[i] != '=')
		return (3);
	return (TRUE);
}

char	*get_var_name(char *str)
{
	char	*match;
	char	*new;
	size_t	i;

	i = 0;
	match = ft_strchr(str, '$');
	if (NULL == match)
		return (NULL);
	match++;
	if (ft_strncmp(match, "?", 1) == 0)
		return (ft_strdup("?"));
	if (ft_strncmp(match, "$", 1) == 0)
		return (ft_strdup("$"));
	if (is_var_name_ok(*match) == FALSE)
		return (NULL);
	while (match[i] && is_var_name_ok(match[i]))
		i++;
	new = malloc(sizeof(char) * i + 1);
	if (NULL == new)
		return (NULL);
	new[i] = '\0';
	while (i--)
		new[i] = match[i];
	return (new);
}

t_list	*locate_env_var(t_list *node, char *name)
{
	t_list	*iter;
	size_t	len;

	iter = node;
	len = 0;
	if (name == NULL)
		return (NULL);
	len = ft_strlen(name);
	while (iter != NULL)
	{
		if (NULL != iter->content && ft_strncmp(name, iter->content, len) == 0)
		{
			if (((char *)iter->content)[len] == '=')
				return (iter);
		}
		iter = iter->next;
	}
	if (iter == NULL)
		return (NULL);
	return (iter);
}
