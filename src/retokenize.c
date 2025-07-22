/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:35 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 16:40:50 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// returns 1 in case of error
int	retokenize(t_shell *shell, t_token *head)
{
	t_token	*iter;
	t_token	*next;

	(void)shell;
	next = head;
	if (NULL == next)
		return (0);
	while (next != NULL)
	{
		iter = next;
		next = iter->next;
		if (next == NULL)
			break ;
		if (!is_token_word(iter->type) || !is_token_word(next->type))
			continue;
		if (FALSE == wrapper_strjoin(&iter->value, next->value))
			exit(1); // WARNING: gestionar salida
		iter->next = next->next;
		delete_token(&head, next);
		iter->type = TOKEN_WORD;
		next = head;
	}
	return (0);
}
