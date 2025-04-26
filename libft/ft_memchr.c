

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*local_s;
	size_t			i;

	local_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (local_s[i] == (unsigned char)c)
			return ((void *)&local_s[i]);
		i++;
	}
	return (NULL);
}
/*
int	main (void)
{
	char	*a = "hola";
	char	c = 'l';
	
	printf ("ft:%s",(char *)ft_memchr(a, c,5));
}*/
