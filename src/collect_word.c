/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:29:33 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/30 18:25:43 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*collect_quote_word(char *str, char delim, int *i, t_token_type *t)
{
	char	*word;
	char	*end;

	end = ft_strchr(str + *i + 1, delim);
	if (end == NULL)
		return (printf("open quote: %c\n", delim), NULL);
	word = ft_substr(str, *i + 1, end - &str[*i] - 1);
	if (NULL != word)
		*i += ft_strlen(word) + 2;
	if (delim == '\'')
		*t = TOKEN_WORD_SQ;
	else
		*t = TOKEN_WORD_DQ;
	return (word);
}

static char	*collect_normal_word(char *line, int *i, t_token_type *type)
{
	char	*word;
	size_t	word_len;
	int		start;

	word_len = 0;
	start = *i;
	while (line[*i] && ft_strchr("'\"\t <>|", line[*i]) == NULL)
	{
		(*i)++;
		word_len++;
	}
	word = ft_substr(line, start, word_len);
	*type = TOKEN_WORD;
	return (word);
}

static char	*handle_locale_aware_strings(char *line, int *i, t_token_type *type)
{
	char	*word;

	(*i)++;
	word = NULL;
	if (line[*i] == '"')
		word = ft_strdup("");
	*type = TOKEN_WORD;
	return (word);
}

int	collect_words(t_token **head, char *line, int *i, t_token_type *type)
{
	char	*word;
	int		word_counter;
	t_token	*last_token;

	if (NULL == line || '\0' == line[*i])
		return (1);
	word_counter = 0;
	while (line[*i] != '\0' && ft_strchr("\t <>|", line[*i]) == NULL)
	{
		if (line[*i] == '$' && line[*i + 1] == '"')
			word = handle_locale_aware_strings(line, i, type);
		else if ('\'' == line[*i] || '"' == line[*i])
			word = collect_quote_word(line, line[*i], i, type);
		else if (line[*i] != '\0' && ft_strchr("\t <>|", line[*i]) == NULL)
			word = collect_normal_word(line, i, type);
		else
			return (0);
		if (NULL == word)
			return (1);
		word_counter++;
		last_token = add_token(head, *type, word);
		if (word_counter > 1)
			last_token->link = 1;
	}
	return (0);
}
