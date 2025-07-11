/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:06:41 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/11 19:15:06 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns a ptr of the node where there's a match
t_list	*locate_env_var(t_list *node, char *var)
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
			if (NULL != iter->content && \
				ft_strncmp(var, iter->content, len) == 0)
			{
				if (((char *)iter->content)[len] == '=')
					break ;
			}
			iter = iter->next;
		}
		if (NULL != iter)
			return (iter);
	}
	return (NULL);
}
