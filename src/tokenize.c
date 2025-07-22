/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:46:01 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/22 18:56:59 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NOTE: Por qué el ";"? Eso es bonus
static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

static t_token_type	detect_operator(char *s, int *i)
{
	if (s[*i] == '|')
	{
		(*i)++;
		return (TOKEN_PIPE);
	}
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		(*i) += 2;
		return (TOKEN_HEREDOC);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		(*i) += 2;
		return (TOKEN_REDIR_APPEND);
	}
	if (s[*i] == '<')
	{
		(*i)++;
		return (TOKEN_REDIR_IN);
	}
	if (s[*i] == '>')
	{
		(*i)++;
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

static t_token	*wrapper_exit(t_token **head)
{
	free_tokens(*head);
	*head = NULL;
	return (NULL);
}

t_token	*tokenize_line(char *line)
{
	t_token			*tokens;
	t_token_type	type;
	int				i;

	tokens = NULL;
	i = 0;
	while (line && line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break ;
		if (line[i] != '\0' && is_special_char(line[i]))
		{
			type = detect_operator(line, &i);
			add_token(&tokens, type, NULL);
		}
		else if (line[i] != '\0')
		{
			if (collect_words(&tokens, line, &i, &type) == 1)
				return (wrapper_exit(&tokens));
		}
	}
	return (tokens);
}
