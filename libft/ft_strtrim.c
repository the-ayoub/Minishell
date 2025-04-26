/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:37:29 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/11 13:28:33 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char *set)
{
	char	*s2;
	int		i;
	int		j;
	int		b;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1)-1;
	while (j >= i && ft_strchr(set, s1[j]))
		j--;
	s2 = (char *)malloc((j - i + 2) * sizeof(char));
	if (!s2)
		return (NULL);
	b = 0;
	while (i <= j)
		s2[b++] = s1[i++];
	s2[b] = '\0';
	return (s2);
}
/*int main (void)
{
	char s[]= "ababbahola que talababbbbaaaba";
	char set[]= "aba";
	Printf("%s\n",ft_strtrim(s,set));
	return (0);
}*/
