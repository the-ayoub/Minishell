/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:56:24 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/09/17 13:20:19 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*local_dest;
	size_t		i;
	const char	*local_src;

	local_src = (const char *)src;
	local_dest = (char *)dest;
	i = 0;
	while (i < n)
	{
		local_dest[i] = local_src[i];
		i++;
	}
	return (dest);
}
/*int	main(void)
{
	char dest[11];
	ft_memcpy(dest, "helloworld", 5);
	dest[5] = '\0';*/
