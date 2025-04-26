

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
