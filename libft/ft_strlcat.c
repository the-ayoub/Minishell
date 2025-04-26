/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 04:31:56 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/11 16:48:47 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>  // Para comparar con la función original

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	i = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (slen + size);
	j = dlen;
	while (src [i] != '\0' && i < size - dlen - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dlen + slen);
}
/*
int	main(void)
{
    char dest[50] = "Hello";
    char src[] = " World!";
    size_t size = 50;
    size_t result;
    size_t result2;

    // Llamada a ft_strlcat
    result = ft_strlcat(dest, src, size);
    printf("Resultado: %s\n", dest);
    printf("Longitud total: %zu\n", result);

    // Comparación con strlcat de la biblioteca estándar
    char dest2[50] = "Hello";
    result2 = strlcat(dest2, src, size);
    printf("Resultado con strlcat: %s\n", dest2);
    printf("Longitud total con strlcat: %zu\n", result);

    return 0;
}
*/
