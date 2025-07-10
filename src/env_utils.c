/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:06:41 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/10 21:29:07 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// WARNING: ft_strncmp is not a good system since it may be the incomplete var
// name
//
// returns a ptr where there's a match with the var
char	*locate_env_var(t_list *node, char *var)
{
	t_list	*iter;
	size_t	len;

	iter = node;
	len = 0;
	if (var != NULL)
	{
		len = ft_strlen(var);
		while (iter != NULL)
		{
			if (ft_strncmp(var, iter->content, len) == 0 || \
				(((char *)iter->content)[len] != '='))
				break ;
			iter = iter->next;
		}
		if (NULL != iter)
			return (iter->content);
	}
	return (NULL);
}
