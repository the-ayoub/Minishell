/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:29:33 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/20 20:11:09 by ohnonon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*collect_quote_word(char *str, char delim, int *i, t_token_type *type)
{
	char	*word;
	char	*end;

	end = ft_strchr(str + *i + 1, delim);
	if (end == NULL)
		return (printf("open quote: %c\n", delim), NULL);
	word = ft_substr(str, *i, end - &str[*i] - 1);
	// word = ft_strtrim(str + *i + 1, &delim);
	if (NULL != word)
		*i += ft_strlen(word) + 2;
	if (delim == '\'')
		*type = TOKEN_WORD_SQ;
	else
		*type = TOKEN_WORD_DQ;
	return (word);
}

char	*collect_word(char *s, int *i, t_token_type *type)
{
	char	*word;
	size_t	word_len;
	int		start;

	if (NULL == s || '\0' == *s)
		return (NULL);
	start = *i;
	if ('\'' == s[*i] || '"' == s[*i])
		return(collect_quote_word(s, s[*i], i, type));
	word_len = 0;
	while (s[*i] && ft_strchr("'\"\t <>|", s[*i]) == NULL)
	{
		(*i)++;
		word_len++;
	}
	word = ft_substr(s, start, word_len);
	if (NULL == word)
		return (NULL);
	*type = TOKEN_WORD;
	return (word);
}
