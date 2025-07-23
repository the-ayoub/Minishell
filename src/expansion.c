/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:39:44 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/23 22:46:19 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*assemble_expansion(char *token_value, t_expand *dt)
{
	char	*new;
	char	*tmp;
	size_t	i;
	size_t	len;

	i = dt->to_expand - token_value;
	new = ft_substr(token_value, 0, i);
	if (new == NULL)
		return (NULL);
	tmp = dt->matching_env;
	dt->matching_env = ft_strchr(dt->matching_env, '=');
	if (dt->matching_env == NULL)
		perror("cant assamble expansion");
	if (wrapper_strjoin(&new, ++dt->matching_env) == FALSE)
		perror("cant assamble expansion");
	len = ft_strlen(dt->var_name) + 1;
	dt->to_expand += len;
	if (wrapper_strjoin(&new, dt->to_expand) == FALSE)
		perror("cant assamble expansion");
	if (dt->false_env == 1)
	{
		free(tmp);
		dt->false_env = 0;
	}
	return (new);
}

static int	aux_upd_node(t_expand *dt, t_list **node, t_shell *shell)
{
	char	*err_str;
	char	*tmp;
	int		check;

	err_str = NULL;
	check = ft_strncmp(dt->var_name, "?", ft_strlen(dt->var_name));
	if (check == 0)
	{
		tmp = ft_itoa(shell->last_status);
		if (tmp)
			err_str = ft_strjoin("=", tmp);
		free(tmp);
		aux_upd_data(dt, dt->to_expand, dt->var_name, err_str);
		dt->false_env = 1;
		return (1);
	}
	*node = locate_env_var(shell->raw_env, dt->var_name);
	if (*node == NULL && ft_strcmp(dt->var_name, "=") == 0)
	{
		aux_upd_data(dt, dt->to_expand, dt->var_name, ft_strdup("="));
		dt->false_env = 1;
	}
	else
		aux_upd_data(dt, dt->to_expand, dt->var_name, (*node)->content);
	return (1);
}

// Retrieves the $str from the tkn.value, then iterates over env
// looking for a match. For no match, returns 1, else 0 there's match
static int	is_expandable(t_token tkn, t_expand *dt, t_shell *shl)
{
	t_list	*node;
	char	*var_name;
	char	*match;
	char	*iter;

	if (tkn.type != TOKEN_WORD_DQ && tkn.type != TOKEN_WORD)
		return (1);
	iter = tkn.value;
	match = NULL;
	while (match == NULL && *iter != '\0')
	{
		match = ft_strchr(iter, '$'); //hay cash
		if (match == NULL)
			return (1);
		var_name = get_var_name(match); // nombre valido
		aux_upd_data(dt, match, var_name, NULL);
		if (var_name != NULL && aux_upd_node(dt, &node, shl))
			break ;
		free(var_name);
		var_name = NULL;
		iter = ++match;
		match = 0;
	}
	if (match == NULL || var_name == NULL)
		return (1);
	return (0);
}

int	expand_variables(t_shell *shell, t_token *head)
{
	t_expand	dt;
	t_token		*tkn;
	char		*tmp;
	
	init_expand(&dt);
	tkn = head;
	while (NULL != tkn)
	{
		free(dt.var_name);
		dt.var_name = NULL;
		dt.token_str = tkn->value;
		if (1 == is_expandable(*tkn, &dt, shell)) // ok
		{
			tkn = tkn->next;
			continue ;
		}
		tmp = assemble_expansion(tkn->value, &dt);
		if (NULL == tmp)
			return (perror("cant expand variable\n"), 1);
		free(tkn->value);
		tkn->value = tmp;
	}
	free(dt.var_name);
	return (0);
}
