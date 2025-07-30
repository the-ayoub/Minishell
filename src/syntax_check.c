/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:53:43 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/30 18:17:50 by nimatura         ###   ########.fr       */
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
			type = current->next->type;
			if (!current->next && type != TOKEN_WORD && type != TOKEN_WORD_SQ \
			&& type != TOKEN_WORD_DQ)
				return (1);
			current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			if (current->next)
				type = current->next->type;
			if (!current->next || type == TOKEN_PIPE)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
