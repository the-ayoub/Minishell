/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:01:21 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/13 18:52:46 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*dest;
	unsigned int		s_len;
	size_t				i;	

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	dest = malloc ((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include<stdio.h>

int main()
{
	char *s = ".";
	int len = ft_strlen(s);
	printf("len = %d, <%s>\n", len, ft_substr(s, 0, len));
}*/
