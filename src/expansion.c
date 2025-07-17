/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/17 18:13:25 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

// Retrieves the variable name from the string
char	*locate_env_var(t_list *env, char *str)
{
	t_list	*iter;
	char	*var_name;
	size_t	len;

	iter = env;
	var_name = NULL;
	while (iter != NULL)
	{
		var_name = ft_strtrim(iter->content, "=");
		if (var_name == NULL) // MALLOC BREAKS
			return ;
		len = ft_strlen(var_name);
		if (ft_strncmp(str, var_name, len) == 0)
			break ;
		iter = iter->next;
	}
	free(var_name);
	if (NULL == iter)
		return (NULL);
	return (iter->content);
}

// WARNING: MALLOC
char	*get_var_name(char *str)
{
	char	*match;

	match = NULL;
	match = ft_strchr(str, '$');
	if (NULL == match)
		return (NULL);
	match++;
	match = ft_strtrim(match, "$ \t"); // MALLOC
	if (NULL == match)
		return (NULL);
	return (match);
}

// Retrieves the $str from the token.value, then iterates over env_lst
// looking for a match. For success, returns 1, else 0 as FALSE
static t_list	*is_expandable(t_token token, char **match)
{
	t_list	*iter;

	if (token.type != TOKEN_WORD_DQ && token.type != TOKEN_WORD)
		return (NULL);
	*match = get_var_name(token.value);
	if (NULL == match)
		return (NULL);
	iter = locate_env_var(iter->content,*match);
	return (iter);
}

char	*assemble_expansion(char *token_value, t_list *env_value, char *var)
{
	char	*prev;
	char	*expansion;
	char	*end;

	if (token_value == NULL || env_value == NULL || var == NULL)
		return (NULL);
	prev = NULL;
	expansion = NULL;
	end = NULL;
	prev = ft_strtrim(token_value, "$");
	if (prev != NULL)
	{
		expansion = ft_strchr(env_value->content, '=');
		expansion++;
		expansion = ft_strdup(expansion);
		if (expansion != NULL)
			end = ft_strjoin(prev, expansion);
	}
	free(expansion);
	free(prev);
	if (end != NULL)
	{
		token_value += ft_strlen(prev) + ft_strlen(var);
		prev = end;
		end = ft_strjoin(end, token_value);
		free(prev);
	}
	return (end);
}

// loops looking for tokens with expandable variables
int	expand_variables(t_shell *shell, t_token *head)
{
	t_token	*iter;
	t_list	*env_var;
	char	*match;
	char	*tmp;
	
	iter = head;
	match = NULL;
	while (NULL != iter)
	{
		env_var = is_expandable(*iter, &match);
		if (env_var != NULL)
		{
			tmp = assemble_expansion(iter->value, env_var, match);
			free(iter->value);
			iter->value = tmp;
			break ;
		}
		iter = iter->next;
	}
	if (iter == NULL)
		return (1);
	return (0);
}
