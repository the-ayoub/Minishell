/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:28:38 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 19:57:19 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->link = 0;
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = create_token(type, value);
	if (!new)
		return (NULL);
	last = NULL;
	if (NULL == *tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	return (new);
}

void	delete_token(t_token **head, t_token *ptr)
{
	t_token	*prev;
	t_token	*next;

	if (head == NULL || *head == NULL || ptr == NULL)
		return ;
	if (ptr == *head)
	{
		next = ptr->next;
		free(ptr->value);
		free(ptr);
		*head = next;
		return ;
	}
	prev = *head;
	while (prev->next != NULL)
	{
		if (prev->next == ptr)
		{
			next = ptr->next;
			free(ptr->value);
			free(ptr);
			prev->next = next;
			return ;
		}
		prev = prev->next;
	}
}
