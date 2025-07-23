/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:06:41 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/23 18:56:55 by nimatura         ###   ########.fr       */
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
			shell->last_status = 1;
			free(var);
		}
	}
	else
		shell->last_status = 1;
	return (shell->last_status);
}

static int	is_var_name_ok(char c)
{
	if (c == ' ' || c == '\t' || c == '\0' || c == '$')
		return (FALSE);
	if (c == '\'' || c == '"')
		return (FALSE);
	return (TRUE);
}

static int	env_key_second_iter(char *str, int *i)
{
	while (str && str[*i] != '\0' && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		while (str[*i] != '\0' && ft_isdigit(str[*i]))
		{
			if (*i == 0)
				return (FALSE);
			i++;
		}
		while (str[*i] != '\0' && ft_isalpha(str[*i]))
			i++;
		while (str[*i] != '\0' && '_' == str[*i])
			i++;
	}
	return (TRUE);
}

// NOTE: SYNTAX
// regex format for valid key is
// [A-Za-z_][A-Za-z0-9_]
int	is_valid_env_key(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (FALSE);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isalpha(str[i]))
		i++;
	if (env_key_second_iter(str, &i) == FALSE)
		return (FALSE);
	if (str[i] != '=')
		return (3);
	if (i == 0)
		return (FALSE);
	return (TRUE);
}

char	*get_var_name(char *str)
{
	char	*match;
	char	*new;
	size_t	i;

	i = 0;
	match = NULL;
	match = ft_strchr(str, '$');
	if (NULL == match)
		return (NULL);
	match++;
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
	// check_special_var(&new);
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
