

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*local_s;
	unsigned int	i;

	local_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		local_s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int main (void)
{
	char a[4] = "aygb";
	int c = 'c';
	int n = 10;
	printf("%s",(char *)ft_memset(a,c,n));
	return (0);
}*/
