/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes </var/spool/mail/ohnudes>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:15:07 by ohnudes           #+#    #+#             */
/*   Updated: 2024/12/24 16:17:26 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/* bitwise strlen

size_t	ft_strlen_bw(const char *str)
{
	const char *char_ptr;
	const unsigned long *longword_ptr;
	unsigned long longword;
	unsigned long himagic;
	unsigned long lomagic;

	char_ptr = str;
	while ((unsigned long)char_ptr & (sizeof(longword) - 1) != 0)
		if (*(char_ptr++) == '\0')
			return (char_ptr - str);

	longword_ptr = (unsigned long *)char_ptr;
	himagic = 0x80808080L;
	lomagic = 0x01010101L;
	while (1)
	{

	}
	if (((longword - lomagic) & ~longword & himahic) != 0)
	{
		const char *cp = (const char *)(longword_ptr - 1);

	}
} */
