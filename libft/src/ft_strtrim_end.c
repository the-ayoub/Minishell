/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:50:39 by ohnonon           #+#    #+#             */
/*   Updated: 2025/07/18 19:17:26 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*aux_end_str(const char *s, const char *set)
{
	size_t	len;

	len = ft_strlen(s);
	while (s[len - 1] && len && ft_strchr(set, s[len - 1]))
		len--;
	return ((char *)s + len - 1);
}

char	*ft_strtrim_end(const char *str, const char *set)
{
	size_t	size;
	char	*end_str;
	char	*new;

	end_str = NULL;
	if (NULL == str)
		return (ft_strdup(""));
	if (*str == '\0')
		return (ft_strdup(""));
	end_str = aux_end_str(str, set);
	size = end_str - str + 1;
	new = ft_substr(str, 0, size);
	return (new);
}
