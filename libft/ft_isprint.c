
#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*#include <stdio.h>
int main (void)
{
	int c;
	c = '8';
	printf("%i",ft_isprint(c));
	return(0);
}*/
