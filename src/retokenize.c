/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:16:35 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/31 20:52:05 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	clean_empty_node(t_token **head)
{
	t_token	*iter;
	t_token	*next;

	iter = *head;
	while (iter != NULL && is_token_word(iter->type))
	{
		next = iter->next;
		if (next == NULL || iter->value == NULL)
			return ;
		if (*iter->value != '\0')
			return ;
		if (is_token_word(next->type) == TRUE)
		{
			if (FALSE == wrapper_strjoin(&iter->value, next->value))
			{
				free_tokens(*head);
				return ;
			}
		}
		delete_token(head, next);
	}
	return ;
}
/*
static void	clean_empty_node(t_token **head)
{
	t_token	*iter;
	t_token	*next;

	next = *head;
	if (next != NULL)
	{
		iter = next;
		next = iter->next;
		if (next == NULL || iter->value == NULL)
			return ;
		if (ft_strcmp(iter->value, "") != 0)
			return ;
		if (FALSE == wrapper_strjoin(&iter->value, next->value))
		{
			free_tokens(*head);
			return ;
		}
		delete_token(head, next);
	}
	return ;
}
*/
static int	guard_heredoc(t_token **head)
{
	t_token	*iter;
	int		total_heredoc;

	total_heredoc = 0;
	iter = *head;
	while (iter != NULL && total_heredoc < 18)
	{
		if (iter->type == TOKEN_HEREDOC)
			total_heredoc++;
		iter = iter->next;
	}
	if (total_heredoc > 17)
		return (FALSE);
	return (TRUE);
}

// returns 1 in case of error
int	retokenize(t_token **head)
{
	t_token	*iter;
	t_token	*next;

	next = *head;
	if (NULL == next)
		return (1);
	if (guard_heredoc(head) == FALSE)
		return (1);
	clean_empty_node(head);
	while (next != NULL)
	{
		iter = next;
		next = iter->next;
		if (next == NULL)
			break ;
		if (next->link != 1)
			continue ;
		if (FALSE == wrapper_strjoin(&iter->value, next->value))
			return (free_tokens(*head), 1);
		delete_token(head, next);
		next = *head;
	}
	return (0);
}
