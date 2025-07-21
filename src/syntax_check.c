/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:53:43 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/21 14:55:51 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// WARNING: If 1 token only, there's no current->next->type
int	syntax_check(t_token *tokens)
{
	t_token			*current;
	t_token_type	type;

	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
		return (1);
	current = tokens;
	while (current)
	{
		if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			type = current->next->type;
			if (!current->next && type != TOKEN_WORD && type != TOKEN_WORD_SQ\
			&& type != TOKEN_WORD_DQ)
				return (1);
			current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			type = current->next->type;
			if (!current->next || type == TOKEN_PIPE)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
