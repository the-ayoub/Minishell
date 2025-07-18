/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/18 19:22:30 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Retrieves the $str from the token.value, then iterates over env_lst
// looking for a match. For success, returns 1, else 0 as FALSE
static t_list	*is_expandable(t_list *env_var, t_token token, char **match)
{
	t_list	*node;

	node = env_var;
	if (token.type != TOKEN_WORD_DQ && token.type != TOKEN_WORD)
		return (NULL);
	if (ft_strchr(token.value, '$') == NULL)
		return (NULL);
	*match = get_var_name(token.value);
	if (NULL == match)
		return (NULL);
	node = locate_env_var(node, *match);
	return (node);
}

static void	aux_exp(char **exp, t_list *env_value, char **prev, char **end)
{
	if (*prev != NULL)
	{
		*exp = ft_strchr(env_value->content, '=');
		(*exp)++;
		*exp = ft_strdup(*exp);
		if (*exp != NULL)
			*end = ft_strjoin(*prev, *exp);
	}
	free(*exp);
	free(*prev);
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
	prev = ft_strtrim_end(token_value, "$");
	printf("check_assamble_exp:token_value: %s\n", token_value);
	printf("check_assamble_exp:prev: %s\n", prev);
	aux_exp(&expansion, env_value, &prev, &end);
	if (end != NULL)
	{
		token_value += ft_strlen(prev) + ft_strlen(var);
		prev = end;
		end = ft_strjoin(end, token_value);
		free(prev);
	}
	free(var);
	return (end);
}

// loops looking for tokens with expandable variables
// returns 1 in case of malloc err
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
		env_var = is_expandable(shell->raw_env, *iter, &match);
		if (env_var != NULL)
		{
			tmp = assemble_expansion(iter->value, env_var, match);
			if (tmp == NULL)
				return (1);
			free(iter->value);
			iter->value = tmp;
			break ;
		}
		iter = iter->next;
	}
	return (0);
}
