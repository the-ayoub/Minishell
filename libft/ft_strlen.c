/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:29:53 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/15 17:10:50 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0')
		counter++;
	return (counter);
}
/*
#include <stdio.h>
int main (void)
{
	char *s;
	s = "hola";
	printf("%zu",ft_strlen(s));
	return (0);
}*/
