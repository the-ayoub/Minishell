/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:35:25 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/09/22 16:53:58 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*local_s;
	size_t			i;

	local_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (local_s[i] == (unsigned char)c)
			return ((void *)&local_s[i]);
		i++;
	}
	return (NULL);
}
/*
int	main (void)
{
	char	*a = "hola";
	char	c = 'l';
	
	printf ("ft:%s",(char *)ft_memchr(a, c,5));
}*/
