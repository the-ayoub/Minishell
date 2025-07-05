/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:12:54 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/15 17:27:13 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*local_s;
	unsigned int	i;

	local_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		local_s[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
int	main (void)
{
	int i = 0;
	char str[9] = "123456789";
	ft_bzero(str, 5);
	while (9 > i)
	{
		if (str[i] == '\0')
			printf("0");
		else
			printf("%c",str[i]);
		i++;
	}
	return (0);
}
*/
