/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnudes <nimatura@student.42barcel>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:38:24 by ohnudes           #+#    #+#             */
/*   Updated: 2024/08/18 20:09:11 by nimatura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

int	aux_stralloc(char **str, size_t size)
{
	if (size == 0)
		*str = NULL;
	else
	{
		*str = malloc(size + 1);
		if (NULL != *str)
			(*str)[size] = '\0';
	}
	return (*str != NULL);
}

size_t	aux_strlen_p(char *str)
{
	size_t	i;

	i = 0;
	if (NULL != str)
		while ('\0' != str[i])
			i++;
	return (i);
}

char	*aux_strchr(char *str, int set)
{
	if (NULL == str)
		return (NULL);
	while ((char )set != *str && '\0' != *str)
		str++;
	if (*str == (char)set)
		return (str);
	return (NULL);
}

char	*aux_strjoin_p(char *dst, char *concat)
{
	char	*str;
	char	*ref;
	char	*iterator;
	size_t	size;

	size = aux_strlen_p(dst) + aux_strlen_p(concat);
	if (0 == aux_stralloc(&str, sizeof(char) * size))
	{
		if (dst != NULL)
			free(dst);
		return (NULL);
	}
	ref = str;
	iterator = dst;
	while (NULL != iterator && '\0' != *iterator)
		*(ref++) = *(iterator++);
	if (NULL != dst)
		free(dst);
	iterator = concat;
	while (concat && *concat != '\0' && *iterator != '\0')
		*(ref++) = *(iterator++);
	return (str);
}

char	*aux_strndup(char *src)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (NULL == src)
		return (NULL);
	len = aux_strlen_p(src);
	str = malloc(sizeof(char) * len + 1);
	if (NULL == str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[i++] = *(src++);
	return (str);
}
