/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:37:06 by aybelhaj          #+#    #+#             */
/*   Updated: 2025/07/15 18:10:27 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NOTE: Por qué el ";"? Eso es bonus
int	is_special_char(char c)
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

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = create_token(type, value);
	if (!new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		last = *tokens;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_token	*tokenize_line(char *line)
{
	t_token			*tokens;
	char			*word;
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
			word = collect_word(line, &i, &type);
			if (NULL == word)
			{
				free_tokens(tokens);
				return (NULL);
			}
			add_token(&tokens, type, word);
		}
	}
	return (tokens);
}
