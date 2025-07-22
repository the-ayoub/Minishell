/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:35 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 20:41:25 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns 1 in case of error
int	retokenize(t_token **head)
{
	t_token	*iter;
	t_token	*next;

	next = *head;
	if (NULL == next)
		return (0);
	while (next != NULL)
	{
		iter = next;
		next = iter->next;
		if (next == NULL)
			break ;
		if (next->link != 1)
			continue;
		if (FALSE == wrapper_strjoin(&iter->value, next->value))
			return (free_tokens(*head), 1);
		delete_token(head, next);
		next = *head;
	}
	return (0);
}
