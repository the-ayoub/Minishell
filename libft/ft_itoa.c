/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:22:46 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/12 17:57:12 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	word_count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*src;
	int				i;
	unsigned int	num;

	i = word_count(n);
	src = ft_calloc(i + 1, sizeof(char));
	src[0] = '0';
	num = n;
	if (n < 0)
	{
		src[0] = '-';
		num = -n;
	}
	while (num > 0)
	{
		src[i - 1] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	return (src);
}
/*int main(void) {
    int n;
    char *test;
    n = -2147483648;
    test = ft_itoa(n);
    printf("%s",test);
    //free(test);
    return 0;
}*/
