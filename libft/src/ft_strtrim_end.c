/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnonon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:50:39 by ohnonon           #+#    #+#             */
/*   Updated: 2025/07/29 19:55:43 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	aux_end_str(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_strchr(set, s[i]))
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim_end(const char *str, const char *set)
{
	size_t	size;
	char	*new;

	if (NULL == str)
		return (ft_strdup(""));
	if (*str == '\0')
		return (ft_strdup(""));
	size = aux_end_str(str, set);
	new = ft_substr(str, 0, size);
	return (new);
}
