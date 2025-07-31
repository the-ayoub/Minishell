/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:53:43 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/31 19:31:44 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	aux_guard(t_token *tokens, t_token **current)
{
	if (!tokens)
		return (FALSE);
	if (tokens->type == TOKEN_PIPE)
		return (FALSE);
	*current = tokens;
	return (TRUE);
}

static int	aux_token_redir(t_token **current, t_token_type *type)
{
	if ((*current)->next != NULL)
		*type = (*current)->next->type;
	if (NULL == (*current)->next && *type != TOKEN_WORD && \
		*type != TOKEN_WORD_SQ && *type != TOKEN_WORD_DQ)
		return (FALSE);
	*current = (*current)->next;
	return (TRUE);
}

static int	aux_token_word(t_token **current, t_token_type *type)
{
	if ((*current)->next)
		*type = (*current)->next->type;
	if (NULL == (*current)->next || *type == TOKEN_PIPE)
		return (FALSE);
	return (TRUE);
}

int	syntax_check(t_token *tokens)
{
	t_token			*current;
	t_token_type	type;

	if (aux_guard(tokens, &current) == FALSE)
		return (1);
	while (current)
	{
		if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			if (aux_token_redir(&current, &type) == FALSE)
				return (1);
		}
		else if (current->type == TOKEN_PIPE)
		{
			if (aux_token_word(&current, &type) == FALSE)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
