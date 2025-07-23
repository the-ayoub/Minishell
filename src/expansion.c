/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/23 20:56:49 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_expand(t_expand *data)
{
	data->token_str = NULL;
	data->to_expand = NULL;
	data->matching_env = NULL;
	data->var_name = NULL;
}

int	aux_upd_data(t_expand *data, char *match, char *var_name, char *env_var)
{
	data->matching_env = env_var;
	data->to_expand = match;
	data->var_name = var_name;
	return (1);
}

char	*assemble_expansion(char *token_value, t_expand *data)
{
	char	*new;
	char	*tmp;
	size_t	i;
	size_t	len;

	i = data->to_expand - token_value;
	new = ft_substr(token_value, 0, i);
	if (new == NULL)
		return (NULL);
	tmp = data->matching_env;
	data->matching_env = ft_strchr(data->matching_env, '=');
	if (data->matching_env == NULL)
		perror("cant assamble expansion");
	if (wrapper_strjoin(&new, ++data->matching_env) == FALSE)
		perror("cant assamble expansion");
	len = ft_strlen(data->var_name) + 1;
	data->to_expand += len;
	if (wrapper_strjoin(&new, data->to_expand) == FALSE)
		perror("cant assamble expansion");
	if (ft_strlen(tmp) == 1)
		free(tmp);
	return (new);
}

// Retrieves the $str from the token.value, then iterates over env_lst
// looking for a match. For success, returns 1, else 0 as FALSE
static int	is_expandable(t_list *env_lst, t_token token, t_expand *data)
{
	t_list	*node;
	char	*var_name;
	char	*match;
	char	*iter;

	if (token.type != TOKEN_WORD_DQ && token.type != TOKEN_WORD)
		return (1);
	iter = token.value;
	match = NULL;
	while (match == NULL && *iter != '\0')
	{
		match = ft_strchr(iter, '$'); //hay cash
		if (match == NULL)
			return (1);
		var_name = get_var_name(match); // nombre valido
		if (var_name != NULL)
		{
			node = locate_env_var(env_lst, var_name);
			if (node == NULL)
			{
				aux_upd_data(data, match, var_name, ft_strdup("="));
				break ;
			}
			else if (node != NULL && aux_upd_data(data, match, var_name, node->content))
				break ;
			free(var_name);
			var_name = NULL;
		}
		iter = ++match;
		match = NULL;
	}
	if (match == NULL || var_name == NULL)
		return (1);
	return (0);
}

int	expand_variables(t_shell *shell, t_token *head)
{
	t_expand	data;
	t_token		*token;
	char		*tmp;
	
	init_expand(&data);
	token = head;
	while (NULL != token)
	{
		free(data.var_name);
		data.var_name = NULL;
		data.token_str = token->value;
		if (1 == is_expandable(shell->raw_env, *token, &data)) // ok
		{
			token = token->next;
			continue ;
		}
		tmp = assemble_expansion(token->value, &data);
		if (NULL == tmp)
		{
			token = token->next;
			continue ;
		}
		free(token->value);
		token->value = tmp;
	}
	free(data.var_name);
	return (0);
}
