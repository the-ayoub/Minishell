/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimatura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:29:33 by nimatura          #+#    #+#             */
/*   Updated: 2025/07/15 16:46:16 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_dollar_in_word(t_list *env, char *word)
{
	char	*value;

	value = get_env_value(t_shell *shell, const char *name);

}

char	*collect_quote_word(char *str, char delim, int *i)
{
	char	*word;
	char	*end;
	int		len;

	end = ft_strchr(str + *i, delim);
	if (end == NULL)
		return (NULL);
	len = end - (str + *i);
	if (len == 0)
		return (ft_strdup(""));
	word = ft_substr(str, *i, len);
	if (NULL != word)
		*i += ft_strlen(word);
	return (word);
}

char	*collect_word(char *s, int *i)
{
	char	*word;
	size_t	word_len;
	int		start;

	if (NULL == s || '\0' == *s)
		return (NULL);
	start = *i;
	if ('\'' == s[*i] || '"' == s[*i])
		return(collect_quote_word(s, s[*i], i));
	word_len = 0;
	while (s[*i] && ft_strchr("'\"\t <>|", s[*i]) == NULL)
	{
		(*i)++;
		word_len++;
	}
	word = ft_substr(s, start, word_len);
	if (NULL == word)
		return (NULL);
	return (word);
}
