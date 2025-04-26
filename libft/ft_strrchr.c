/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:07:40 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/01 10:13:03 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i-- > 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
	}
	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *s = "hola lu";
	char c = '\0';

	printf("%s",ft_strrchr(s, c));
	printf("%p\n",ft_strrchr(s, c));
	printf("%p", s);
}*/
