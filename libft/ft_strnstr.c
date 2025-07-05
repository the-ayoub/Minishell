/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:54:51 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/12 18:29:47 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	if (!big)
		return (0);
	if (*little == '\0')
		return ((char *)big);
	i = 0;
	n = ft_strlen(little);
	while (i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && len > (i + j))
		{
			j++;
			if (n == j)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char big[] = "Hola mun mund mundo ayoub";
	char little[] = "";
	printf("Resultat: %s ", ft_strnstr(big,little,10));
	return (0);
}*/
