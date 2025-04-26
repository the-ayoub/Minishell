/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:02:45 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/10/15 19:03:12 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static char	*get_next_word(char const **s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)*s;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	*s += i;
	str = ft_substr(str, 0, i);
	return (str);
}

static void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**new;
	int		y;

	y = 0;
	j = count_words((char *)s, c);
	new = (char **)malloc((j + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			new[y] = get_next_word(&s, c);
			if (!new[y++])
			{
				free_array(new);
				return (NULL);
			}
		}
		else
			s++;
	}
	new[y] = NULL;
	return (new);
}
/*
#include <stdio.h>

int	main(void)
{
	// char	str[];
	char	c;
	char	**res;
	int		i;

	//str[] = "     hola  que  tal";
	char str[] = "lorem ipsum dolor sit amet, 
	consectetur adipiscing elit. Sed non risus. 
	Suspendisse lectus tortor, dignissim sit amet, 
	adipiscing nec, ultricies sed, dolor. Cras 
	elementum ultricies diam. Maecenas ligula massa, 
	varius a, semper congue, euismod non, mi.";
	c = 'i';
	res = ft_split(str, c);
	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	free_array(res);
	return (0);
}*/
