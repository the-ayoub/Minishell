

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;

	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nmemb * size);
	return (tmp);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%p\n",calloc(2147483659,1));
}*/
