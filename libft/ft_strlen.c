
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	if (!s)
		return (0);
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
