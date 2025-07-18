/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:06:41 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/18 17:57:48 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// WARNING: MALLOC
// Receives a string and looks for a '$' sign. It will strdup the following
// content until a space, tab, cash or null char are found. It will return
// a new allocated str at success, otherwise NULL.
char	*get_var_name(char *str)
{
	char	*match;

	match = NULL;
	match = ft_strchr(str, '$');
	if (NULL == match)
		return (NULL);
	match++;
	if (*match == ' ' || *match == '\t' || *match == '\0' || *match == '$')
		return (NULL);
	match = ft_strtrim_end(match, "$ \t"); // MALLOC
	if (NULL == match)
		return (NULL);
	return (match);
}

// Iterates over the list looking for a comparaison of the name str and the
// start of each env_var node. In case of a match, it returns the node,
// otherwise NULL
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
