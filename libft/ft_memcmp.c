/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:49:55 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/09/17 20:42:38 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*local_s1;
	size_t			i;
	unsigned char	*local_s2;

	local_s1 = (unsigned char *)s1;
	local_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (local_s1[i] != local_s2[i])
			return (local_s1[i] - local_s2[i]);
		i++;
	}
	return (0);
}
